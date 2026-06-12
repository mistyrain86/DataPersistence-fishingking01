#pragma once
#include <string>
#include <vector>
#include <optional>
#include "../Model/Order.h"
#include "../Model/OrderRepository.h"
#include "../Model/SampleRepository.h"

enum class ApproveResult {
    SUCCESS_CONFIRMED,
    SUCCESS_PRODUCING,
    FAILED
};

class OrderController {
public:
    OrderController(OrderRepository& orderRepo, SampleRepository& sampleRepo);

    bool                  reserveOrder(const std::string& sampleId,
                                       const std::string& customerName,
                                       int quantity);
    ApproveResult         approveOrder(const std::string& orderId);
    bool                  rejectOrder(const std::string& orderId);
    std::vector<Order>    getReservedOrders() const;
    std::vector<Order>    getAllOrders() const;
    std::optional<Order>  getOrderById(const std::string& id) const;

private:
    OrderRepository&  orderRepo_;
    SampleRepository& sampleRepo_;
    static int        idCounter_;

    // 필요 생산량 = ceil(주문량 / (수율 * 0.9))
    int calcRequiredProduction(int orderQty, double yield) const;
};
