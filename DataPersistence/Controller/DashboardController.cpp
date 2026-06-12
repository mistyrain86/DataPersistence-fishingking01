#include "DashboardController.h"

DashboardController::DashboardController(OrderRepository& orderRepo,
                                          SampleRepository& sampleRepo)
    : orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

DashboardData DashboardController::getDashboardData() const {
    DashboardData data{};
    data.reservedCount  = static_cast<int>(orderRepo_.findByStatus(OrderStatus::RESERVED).size());
    data.confirmedCount = static_cast<int>(orderRepo_.findByStatus(OrderStatus::CONFIRMED).size());
    data.producingCount = static_cast<int>(orderRepo_.findByStatus(OrderStatus::PRODUCING).size());
    data.releaseCount   = static_cast<int>(orderRepo_.findByStatus(OrderStatus::RELEASE).size());

    for (const auto& sample : sampleRepo_.findAll()) {
        SampleStatus ss{};
        ss.sample = sample;
        for (const auto& order : orderRepo_.findBySampleId(sample.id)) {
            switch (order.status) {
            case OrderStatus::RESERVED:  ss.reservedQty  += order.quantity; break;
            case OrderStatus::CONFIRMED: ss.confirmedQty += order.quantity; break;
            case OrderStatus::PRODUCING: ss.producingQty += order.quantity; break;
            case OrderStatus::RELEASE:   ss.releasedQty  += order.quantity; break;
            default: break;
            }
        }
        data.sampleStatuses.push_back(ss);
    }
    return data;
}
