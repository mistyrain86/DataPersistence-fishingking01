#include "ReleaseView.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

ReleaseView::ReleaseView(ReleaseController& ctrl) : ctrl_(ctrl) {}

void ReleaseView::showMenu() {
    std::cout << "\n========== [출고 처리] ==========\n";
    std::cout << "  1. 출고 가능 주문 조회 (CONFIRMED)\n";
    std::cout << "  2. 출고 처리\n";
    std::cout << "  0. 이전 메뉴\n";
    std::cout << "=================================\n";
    std::cout << "선택 > ";
}

void ReleaseView::run() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case 1: doListConfirmed(); break;
        case 2: doRelease();       break;
        case 0: break;
        default:
            std::cout << "[오류] 잘못된 입력입니다.\n";
        }
    }
}

void ReleaseView::doListConfirmed() {
    auto orders = ctrl_.getConfirmedOrders();
    std::cout << "\n-- 출고 가능 주문 (CONFIRMED, " << orders.size() << "건) --\n";
    if (orders.empty()) { std::cout << "  출고 가능한 주문이 없습니다.\n"; return; }
    std::cout << std::left
              << std::setw(8)  << "주문ID"
              << std::setw(8)  << "시료ID"
              << std::setw(16) << "고객명"
              << std::setw(8)  << "수량"
              << "주문일시\n";
    std::cout << std::string(60, '-') << "\n";
    for (const auto& o : orders) printOrder(o);
}

void ReleaseView::doRelease() {
    auto orders = ctrl_.getConfirmedOrders();
    if (orders.empty()) {
        std::cout << "\n[안내] 출고 가능한 주문이 없습니다.\n"; return;
    }
    doListConfirmed();
    std::string orderId;
    std::cout << "출고 처리할 주문 ID : "; std::getline(std::cin, orderId);

    if (ctrl_.releaseOrder(orderId))
        std::cout << "[완료] 출고 처리 완료 → RELEASE\n";
    else
        std::cout << "[오류] 해당 주문을 찾을 수 없거나 CONFIRMED 상태가 아닙니다.\n";
}

void ReleaseView::printOrder(const Order& o) const {
    std::cout << std::left
              << std::setw(8)  << o.id
              << std::setw(8)  << o.sampleId
              << std::setw(16) << o.customerName
              << std::setw(8)  << o.quantity
              << o.orderedAt << "\n";
}
