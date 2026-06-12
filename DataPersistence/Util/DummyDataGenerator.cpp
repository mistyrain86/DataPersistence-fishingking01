#include "DummyDataGenerator.h"
#include <iostream>

DummyDataGenerator::DummyDataGenerator(SampleRepository& sampleRepo,
                                        OrderRepository& orderRepo)
    : sampleRepo_(sampleRepo), orderRepo_(orderRepo) {}

void DummyDataGenerator::generate() {
    // 시료 5개 등록
    sampleRepo_.add({ "S1", "웨이퍼-200mm",  500, 0.92, 2.0, "2025-01-10 09:00:00" });
    sampleRepo_.add({ "S2", "웨이퍼-300mm",  300, 0.88, 3.5, "2025-01-12 10:30:00" });
    sampleRepo_.add({ "S3", "SiC 기판",      150, 0.85, 5.0, "2025-02-01 08:00:00" });
    sampleRepo_.add({ "S4", "GaN 에피층",     80, 0.90, 4.0, "2025-02-15 14:00:00" });
    sampleRepo_.add({ "S5", "산화막 시료",   200, 0.95, 1.5, "2025-03-01 11:00:00" });

    // 주문 10개 등록 (다양한 상태)
    orderRepo_.add({ "ORD1",  "S1", "삼성전자",  100, OrderStatus::CONFIRMED, "2025-03-10 09:00:00", 0   });
    orderRepo_.add({ "ORD2",  "S2", "SK하이닉스", 50, OrderStatus::RESERVED,  "2025-03-11 10:00:00", 0   });
    orderRepo_.add({ "ORD3",  "S3", "TSMC 코리아",200, OrderStatus::PRODUCING,"2025-03-12 11:00:00", 261 });
    orderRepo_.add({ "ORD4",  "S4", "인텔코리아",  30, OrderStatus::RELEASE,  "2025-03-13 13:00:00", 0   });
    orderRepo_.add({ "ORD5",  "S5", "마이크론",    80, OrderStatus::CONFIRMED, "2025-03-14 09:30:00", 0   });
    orderRepo_.add({ "ORD6",  "S1", "DB하이텍",    60, OrderStatus::RESERVED,  "2025-03-15 10:00:00", 0   });
    orderRepo_.add({ "ORD7",  "S2", "네패스",      90, OrderStatus::PRODUCING, "2025-03-16 15:00:00", 114 });
    orderRepo_.add({ "ORD8",  "S3", "앰코테크",    40, OrderStatus::REJECTED,  "2025-03-17 09:00:00", 0   });
    orderRepo_.add({ "ORD9",  "S4", "LX세미콘",    20, OrderStatus::RESERVED,  "2025-03-18 11:30:00", 0   });
    orderRepo_.add({ "ORD10", "S5", "동운아나텍",  50, OrderStatus::CONFIRMED, "2025-03-19 14:00:00", 0   });

    std::cout << "[더미 데이터] 시료 5건, 주문 10건이 생성되었습니다.\n";
}
