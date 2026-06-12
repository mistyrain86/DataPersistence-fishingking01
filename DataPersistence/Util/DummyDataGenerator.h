#pragma once
#include "../Model/SampleRepository.h"
#include "../Model/OrderRepository.h"

class DummyDataGenerator {
public:
    DummyDataGenerator(SampleRepository& sampleRepo, OrderRepository& orderRepo);

    // 시료 5개, 주문 10개 더미 데이터 생성
    void generate();

private:
    SampleRepository& sampleRepo_;
    OrderRepository&  orderRepo_;
};
