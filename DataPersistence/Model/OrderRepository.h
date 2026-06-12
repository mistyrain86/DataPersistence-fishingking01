#pragma once
#include <vector>
#include <optional>
#include <string>
#include "Order.h"

class OrderRepository {
public:
    explicit OrderRepository(std::string filePath = "");

    void                   add(const Order& order);
    std::optional<Order>   findById(const std::string& id) const;
    std::vector<Order>     findAll() const;
    std::vector<Order>     findByStatus(OrderStatus status) const;
    std::vector<Order>     findBySampleId(const std::string& sampleId) const;
    bool                   update(const Order& order);
    int                    count() const;

private:
    void load();
    void save() const;

    std::vector<Order> orders_;
    std::string        filePath_;
};
