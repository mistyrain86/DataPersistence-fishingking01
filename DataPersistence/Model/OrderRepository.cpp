#include "OrderRepository.h"
#include <algorithm>
#include <fstream>
#include "../Util/json.hpp"

using json = nlohmann::json;

static OrderStatus statusFromString(const std::string& s) {
    if (s == "RESERVED")  return OrderStatus::RESERVED;
    if (s == "REJECTED")  return OrderStatus::REJECTED;
    if (s == "PRODUCING") return OrderStatus::PRODUCING;
    if (s == "CONFIRMED") return OrderStatus::CONFIRMED;
    if (s == "RELEASE")   return OrderStatus::RELEASE;
    return OrderStatus::RESERVED;
}

static json orderToJson(const Order& o) {
    return {
        {"id",                 o.id},
        {"sampleId",           o.sampleId},
        {"customerName",       o.customerName},
        {"quantity",           o.quantity},
        {"status",             toString(o.status)},
        {"orderedAt",          o.orderedAt},
        {"requiredProduction", o.requiredProduction}
    };
}

static Order orderFromJson(const json& j) {
    Order o;
    o.id                 = j.at("id").get<std::string>();
    o.sampleId           = j.at("sampleId").get<std::string>();
    o.customerName       = j.at("customerName").get<std::string>();
    o.quantity           = j.at("quantity").get<int>();
    o.status             = statusFromString(j.at("status").get<std::string>());
    o.orderedAt          = j.at("orderedAt").get<std::string>();
    o.requiredProduction = j.at("requiredProduction").get<int>();
    return o;
}

OrderRepository::OrderRepository(std::string filePath)
    : filePath_(std::move(filePath))
{
    if (!filePath_.empty())
        load();
}

void OrderRepository::add(const Order& order) {
    orders_.push_back(order);
    save();
}

std::optional<Order> OrderRepository::findById(const std::string& id) const {
    for (const auto& o : orders_)
        if (o.id == id) return o;
    return std::nullopt;
}

std::vector<Order> OrderRepository::findAll() const {
    return orders_;
}

std::vector<Order> OrderRepository::findByStatus(OrderStatus status) const {
    std::vector<Order> result;
    for (const auto& o : orders_)
        if (o.status == status) result.push_back(o);
    return result;
}

std::vector<Order> OrderRepository::findBySampleId(const std::string& sampleId) const {
    std::vector<Order> result;
    for (const auto& o : orders_)
        if (o.sampleId == sampleId) result.push_back(o);
    return result;
}

bool OrderRepository::update(const Order& order) {
    for (auto& o : orders_) {
        if (o.id == order.id) { o = order; save(); return true; }
    }
    return false;
}

int OrderRepository::count() const {
    return static_cast<int>(orders_.size());
}

void OrderRepository::load() {
    std::ifstream f(filePath_);
    if (!f.is_open()) return;
    try {
        json j = json::parse(f);
        for (const auto& item : j)
            orders_.push_back(orderFromJson(item));
    } catch (...) {}
}

void OrderRepository::save() const {
    if (filePath_.empty()) return;
    json j = json::array();
    for (const auto& o : orders_)
        j.push_back(orderToJson(o));
    std::ofstream f(filePath_);
    if (f.is_open())
        f << j.dump(2);
}
