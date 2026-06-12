#include "DashboardView.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

DashboardView::DashboardView(DashboardController& ctrl) : ctrl_(ctrl) {}

void DashboardView::showMenu() {
    std::cout << "\n========== [대시보드] ==========\n";
    std::cout << "  1. 주문 현황 조회\n";
    std::cout << "  2. 시료별 현황 조회\n";
    std::cout << "  0. 이전 메뉴\n";
    std::cout << "================================\n";
    std::cout << "선택 > ";
}

void DashboardView::run() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case 1: doShowOrderStatus();  break;
        case 2: doShowSampleStatus(); break;
        case 0: break;
        default:
            std::cout << "[오류] 잘못된 입력입니다.\n";
        }
    }
}

void DashboardView::doShowOrderStatus() {
    auto data = ctrl_.getDashboardData();
    int total = data.reservedCount + data.confirmedCount
              + data.producingCount + data.releaseCount;

    std::cout << "\n========== 주문 현황 ==========\n";
    std::cout << std::left
              << std::setw(16) << "  RESERVED"  << data.reservedCount  << "건\n"
              << std::setw(16) << "  CONFIRMED" << data.confirmedCount << "건\n"
              << std::setw(16) << "  PRODUCING" << data.producingCount << "건\n"
              << std::setw(16) << "  RELEASE"   << data.releaseCount   << "건\n";
    std::cout << std::string(30, '-') << "\n";
    std::cout << std::setw(16) << "  합계" << total << "건\n";
    std::cout << "  (* REJECTED 제외)\n";
}

void DashboardView::doShowSampleStatus() {
    auto data = ctrl_.getDashboardData();
    std::cout << "\n========== 시료별 현황 ==========\n";
    if (data.sampleStatuses.empty()) {
        std::cout << "  등록된 시료가 없습니다.\n"; return;
    }
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(18) << "이름"
              << std::setw(8)  << "재고"
              << std::setw(10) << "예약"
              << std::setw(10) << "확정"
              << std::setw(10) << "생산중"
              << std::setw(10) << "출고\n";
    std::cout << std::string(72, '-') << "\n";
    for (const auto& ss : data.sampleStatuses) {
        std::cout << std::left
                  << std::setw(6)  << ss.sample.id
                  << std::setw(18) << ss.sample.name
                  << std::setw(8)  << ss.sample.quantity
                  << std::setw(10) << ss.reservedQty
                  << std::setw(10) << ss.confirmedQty
                  << std::setw(10) << ss.producingQty
                  << std::setw(10) << ss.releasedQty << "\n";
    }
}
