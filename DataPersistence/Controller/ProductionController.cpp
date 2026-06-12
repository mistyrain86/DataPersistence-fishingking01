#include "ProductionController.h"

ProductionController::ProductionController(OrderRepository& orderRepo,
                                            SampleRepository& sampleRepo)
    : orderRepo_(orderRepo), sampleRepo_(sampleRepo) {}

std::vector<ProductionInfo> ProductionController::getProductionQueue() const {
    std::vector<ProductionInfo> queue;
    // FIFO: findByStatus는 등록 순서(insertion order)를 유지
    for (const auto& order : orderRepo_.findByStatus(OrderStatus::PRODUCING)) {
        auto sample = sampleRepo_.findById(order.sampleId);
        if (!sample) continue;
        double hours = sample->cycleTime * order.requiredProduction;
        queue.push_back({ order, *sample, hours });
    }
    return queue;
}

bool ProductionController::completeProduction(const std::string& orderId) {
    auto order = orderRepo_.findById(orderId);
    if (!order || order->status != OrderStatus::PRODUCING) return false;

    // 생산 완료: PRODUCING → CONFIRMED
    auto o   = *order;
    o.status = OrderStatus::CONFIRMED;
    orderRepo_.update(o);
    return true;
}
