#pragma once
#include <string>

struct Sample {
    std::string id;
    std::string name;
    int         quantity;    // 재고 수량
    double      yield;       // 수율 (0.0 ~ 1.0)
    double      cycleTime;   // 생산 사이클타임 (시간/개)
    std::string registeredAt;
};
