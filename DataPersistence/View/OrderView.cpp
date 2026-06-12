#include "OrderView.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

OrderView::OrderView(OrderController& orderCtrl, SampleController& sampleCtrl)
    : orderCtrl_(orderCtrl), sampleCtrl_(sampleCtrl) {}

void OrderView::showMenu() {
    std::cout << "\n========== [주문 관리] ==========\n";
    std::cout << "  1. 주문 예약\n";
    std::cout << "  2. 전체 주문 조회\n";
    std::cout << "  3. 예약 주문 조회 (RESERVED)\n";
    std::cout << "  4. 주문 승인 / 거절\n";
    std::cout << "  0. 이전 메뉴\n";
    std::cout << "=================================\n";
    std::cout << "선택 > ";
}

void OrderView::run() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case 1: doReserveOrder();       break;
        case 2: doListAllOrders();      break;
        case 3: doListReservedOrders(); break;
        case 4: doApproveOrReject();    break;
        case 0: break;
        default:
            std::cout << "[오류] 잘못된 입력입니다.\n";
        }
    }
}

void OrderView::doReserveOrder() {
    std::cout << "\n-- 주문 예약 --\n";

    // 현재 시료 목록 표시
    auto samples = sampleCtrl_.getAllSamples();
    if (samples.empty()) {
        std::cout << "[오류] 등록된 시료가 없습니다.\n"; return;
    }
    std::cout << "[시료 목록]\n";
    for (const auto& s : samples)
        std::cout << "  " << s.id << " | " << s.name
                  << " (재고: " << s.quantity << ")\n";

    std::string sampleId, customerName;
    int quantity;
    std::cout << "시료 ID     : "; std::getline(std::cin, sampleId);
    std::cout << "고객명      : "; std::getline(std::cin, customerName);
    std::cout << "주문 수량   : "; std::cin >> quantity;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (orderCtrl_.reserveOrder(sampleId, customerName, quantity))
        std::cout << "[완료] 주문이 예약되었습니다. (상태: RESERVED)\n";
    else
        std::cout << "[오류] 시료 ID가 존재하지 않습니다.\n";
}

void OrderView::doListAllOrders() {
    auto orders = orderCtrl_.getAllOrders();
    std::cout << "\n-- 전체 주문 (" << orders.size() << "건) --\n";
    if (orders.empty()) { std::cout << "  주문이 없습니다.\n"; return; }
    std::cout << std::left
              << std::setw(8)  << "주문ID"
              << std::setw(8)  << "시료ID"
              << std::setw(16) << "고객명"
              << std::setw(8)  << "수량"
              << std::setw(12) << "상태"
              << "주문일시\n";
    std::cout << std::string(70, '-') << "\n";
    for (const auto& o : orders) printOrder(o);
}

void OrderView::doListReservedOrders() {
    auto orders = orderCtrl_.getReservedOrders();
    std::cout << "\n-- 예약 주문 (RESERVED, " << orders.size() << "건) --\n";
    if (orders.empty()) { std::cout << "  예약 주문이 없습니다.\n"; return; }
    for (const auto& o : orders) printOrder(o);
}

void OrderView::doApproveOrReject() {
    auto reserved = orderCtrl_.getReservedOrders();
    if (reserved.empty()) {
        std::cout << "\n[안내] 처리할 예약 주문이 없습니다.\n"; return;
    }
    std::cout << "\n-- 예약 주문 목록 --\n";
    for (const auto& o : reserved) printOrder(o);

    std::string orderId;
    std::cout << "처리할 주문 ID : "; std::getline(std::cin, orderId);
    std::cout << "1. 승인  2. 거절  > ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
        auto result = orderCtrl_.approveOrder(orderId);
        if (result == ApproveResult::SUCCESS_CONFIRMED)
            std::cout << "[완료] 주문 승인 - 재고 충분 → CONFIRMED\n";
        else if (result == ApproveResult::SUCCESS_PRODUCING)
            std::cout << "[완료] 주문 승인 - 재고 부족 → 생산 중 (PRODUCING)\n";
        else
            std::cout << "[오류] 승인에 실패했습니다.\n";
    } else if (choice == 2) {
        if (orderCtrl_.rejectOrder(orderId))
            std::cout << "[완료] 주문이 거절되었습니다. (REJECTED)\n";
        else
            std::cout << "[오류] 거절에 실패했습니다.\n";
    }
}

void OrderView::printOrder(const Order& o) const {
    std::cout << std::left
              << std::setw(8)  << o.id
              << std::setw(8)  << o.sampleId
              << std::setw(16) << o.customerName
              << std::setw(8)  << o.quantity
              << std::setw(12) << toString(o.status)
              << o.orderedAt << "\n";
}
