#pragma once
#include <vector>
#include <string>
#include "../Model/Order.h"
#include "../Model/OrderRepository.h"

class ReleaseController {
public:
    explicit ReleaseController(OrderRepository& orderRepo);

    std::vector<Order> getConfirmedOrders() const;
    bool               releaseOrder(const std::string& orderId);

private:
    OrderRepository& orderRepo_;
};
