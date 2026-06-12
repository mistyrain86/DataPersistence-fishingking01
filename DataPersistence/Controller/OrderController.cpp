#include "OrderController.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cmath>

int OrderController::idCounter_ = 0;

namespace {
    std::string currentTimeStr() {
        auto now = std::chrono::system_clock::now();
        auto t   = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
        localtime_s(&tm, &t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
}

OrderController::OrderController(OrderRepository& orderRepo, SampleRepository& sampleRepo)
    : orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

bool OrderController::reserveOrder(const std::string& sampleId,
                                    const std::string& customerName,
                                    int quantity) {
    if (!sampleRepo_.findById(sampleId)) return false;

    Order o;
    o.id                 = "ORD" + std::to_string(++idCounter_);
    o.sampleId           = sampleId;
    o.customerName       = customerName;
    o.quantity           = quantity;
    o.status             = OrderStatus::RESERVED;
    o.orderedAt          = currentTimeStr();
    o.requiredProduction = 0;
    orderRepo_.add(o);
    return true;
}

ApproveResult OrderController::approveOrder(const std::string& orderId) {
    auto order  = orderRepo_.findById(orderId);
    if (!order || order->status != OrderStatus::RESERVED) return ApproveResult::FAILED;

    auto sample = sampleRepo_.findById(order->sampleId);
    if (!sample) return ApproveResult::FAILED;

    auto o = *order;
    if (sample->quantity >= o.quantity) {
        // 재고 충분 → CONFIRMED, 재고 차감
        auto s   = *sample;
        s.quantity -= o.quantity;
        sampleRepo_.update(s);
        o.status = OrderStatus::CONFIRMED;
        orderRepo_.update(o);
        return ApproveResult::SUCCESS_CONFIRMED;
    } else {
        // 재고 부족 → PRODUCING
        o.requiredProduction = calcRequiredProduction(o.quantity, sample->yield);
        o.status             = OrderStatus::PRODUCING;
        orderRepo_.update(o);
        return ApproveResult::SUCCESS_PRODUCING;
    }
}

bool OrderController::rejectOrder(const std::string& orderId) {
    auto order = orderRepo_.findById(orderId);
    if (!order || order->status != OrderStatus::RESERVED) return false;
    auto o   = *order;
    o.status = OrderStatus::REJECTED;
    orderRepo_.update(o);
    return true;
}

std::vector<Order> OrderController::getReservedOrders() const {
    return orderRepo_.findByStatus(OrderStatus::RESERVED);
}

std::vector<Order> OrderController::getAllOrders() const {
    return orderRepo_.findAll();
}

std::optional<Order> OrderController::getOrderById(const std::string& id) const {
    return orderRepo_.findById(id);
}

int OrderController::calcRequiredProduction(int orderQty, double yield) const {
    return static_cast<int>(std::ceil(orderQty / (yield * 0.9)));
}
