#include "ProductionView.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

ProductionView::ProductionView(ProductionController& ctrl) : ctrl_(ctrl) {}

void ProductionView::showMenu() {
    std::cout << "\n========== [생산 관리] ==========\n";
    std::cout << "  1. 생산 대기열 조회 (FIFO)\n";
    std::cout << "  2. 생산 완료 처리\n";
    std::cout << "  0. 이전 메뉴\n";
    std::cout << "=================================\n";
    std::cout << "선택 > ";
}

void ProductionView::run() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case 1: doShowQueue();           break;
        case 2: doCompleteProduction();  break;
        case 0: break;
        default:
            std::cout << "[오류] 잘못된 입력입니다.\n";
        }
    }
}

void ProductionView::doShowQueue() {
    auto queue = ctrl_.getProductionQueue();
    std::cout << "\n-- 생산 대기열 (" << queue.size() << "건, FIFO 순서) --\n";
    if (queue.empty()) { std::cout << "  생산 중인 주문이 없습니다.\n"; return; }

    std::cout << std::left
              << std::setw(8)  << "주문ID"
              << std::setw(18) << "시료명"
              << std::setw(10) << "주문수량"
              << std::setw(12) << "필요생산량"
              << "예상시간(h)\n";
    std::cout << std::string(60, '-') << "\n";
    for (const auto& info : queue) {
        std::cout << std::left
                  << std::setw(8)  << info.order.id
                  << std::setw(18) << info.sample.name
                  << std::setw(10) << info.order.quantity
                  << std::setw(12) << info.order.requiredProduction
                  << std::fixed << std::setprecision(1) << info.estimatedHours << "\n";
    }
}

void ProductionView::doCompleteProduction() {
    auto queue = ctrl_.getProductionQueue();
    if (queue.empty()) {
        std::cout << "\n[안내] 생산 중인 주문이 없습니다.\n"; return;
    }
    doShowQueue();
    std::string orderId;
    std::cout << "완료 처리할 주문 ID : "; std::getline(std::cin, orderId);

    if (ctrl_.completeProduction(orderId))
        std::cout << "[완료] 생산 완료 → CONFIRMED 전환\n";
    else
        std::cout << "[오류] 해당 주문을 찾을 수 없거나 PRODUCING 상태가 아닙니다.\n";
}
