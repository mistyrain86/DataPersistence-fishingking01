#pragma once
#include <string>
#include "OrderStatus.h"

struct Order {
    std::string id;
    std::string sampleId;
    std::string customerName;
    int         quantity;
    OrderStatus status;
    std::string orderedAt;
    int         requiredProduction;  // 필요 생산량 (PRODUCING 상태)
};
