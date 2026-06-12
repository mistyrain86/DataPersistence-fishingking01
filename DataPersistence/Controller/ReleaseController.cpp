#include "ReleaseController.h"

ReleaseController::ReleaseController(OrderRepository& orderRepo)
    : orderRepo_(orderRepo) {}

std::vector<Order> ReleaseController::getConfirmedOrders() const {
    return orderRepo_.findByStatus(OrderStatus::CONFIRMED);
}

bool ReleaseController::releaseOrder(const std::string& orderId) {
    auto order = orderRepo_.findById(orderId);
    if (!order || order->status != OrderStatus::CONFIRMED) return false;
    auto o   = *order;
    o.status = OrderStatus::RELEASE;
    orderRepo_.update(o);
    return true;
}
