#pragma once
#include <vector>
#include "../Model/Sample.h"
#include "../Model/Order.h"
#include "../Model/SampleRepository.h"
#include "../Model/OrderRepository.h"

struct SampleStatus {
    Sample sample;
    int    reservedQty;
    int    confirmedQty;
    int    producingQty;
    int    releasedQty;
};

struct DashboardData {
    int                      reservedCount;
    int                      confirmedCount;
    int                      producingCount;
    int                      releaseCount;
    std::vector<SampleStatus> sampleStatuses;
};

class DashboardController {
public:
    DashboardController(OrderRepository& orderRepo, SampleRepository& sampleRepo);

    DashboardData getDashboardData() const;

private:
    OrderRepository&  orderRepo_;
    SampleRepository& sampleRepo_;
};
