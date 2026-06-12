#pragma once
#include <vector>
#include <string>
#include "../Model/Order.h"
#include "../Model/Sample.h"
#include "../Model/OrderRepository.h"
#include "../Model/SampleRepository.h"

struct ProductionInfo {
    Order  order;
    Sample sample;
    double estimatedHours;  // cycleTime * requiredProduction
};

class ProductionController {
public:
    ProductionController(OrderRepository& orderRepo, SampleRepository& sampleRepo);

    // FIFO 순서로 생산 대기열 반환
    std::vector<ProductionInfo> getProductionQueue() const;
    bool                        completeProduction(const std::string& orderId);

private:
    OrderRepository&  orderRepo_;
    SampleRepository& sampleRepo_;
};
