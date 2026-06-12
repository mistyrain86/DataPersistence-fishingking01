#include "SampleView.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

SampleView::SampleView(SampleController& ctrl) : ctrl_(ctrl) {}

void SampleView::showMenu() {
    std::cout << "\n========== [시료 관리] ==========\n";
    std::cout << "  1. 시료 추가\n";
    std::cout << "  2. 시료 목록 조회\n";
    std::cout << "  3. 시료 검색 (이름)\n";
    std::cout << "  0. 이전 메뉴\n";
    std::cout << "=================================\n";
    std::cout << "선택 > ";
}

void SampleView::run() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case 1: doAddSample();    break;
        case 2: doListSamples();  break;
        case 3: doSearchSample(); break;
        case 0: break;
        default:
            std::cout << "[오류] 잘못된 입력입니다.\n";
        }
    }
}

void SampleView::doAddSample() {
    std::string name;
    int    quantity;
    double yield, cycleTime;

    std::cout << "\n-- 시료 추가 --\n";
    std::cout << "이름        : "; std::getline(std::cin, name);
    std::cout << "재고 수량   : "; std::cin >> quantity;
    std::cout << "수율 (0~1)  : "; std::cin >> yield;
    std::cout << "사이클타임  : "; std::cin >> cycleTime;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (ctrl_.addSample(name, quantity, yield, cycleTime))
        std::cout << "[완료] 시료 '" << name << "' 이(가) 등록되었습니다.\n";
    else
        std::cout << "[오류] 시료 등록에 실패했습니다.\n";
}

void SampleView::doListSamples() {
    auto samples = ctrl_.getAllSamples();
    std::cout << "\n-- 시료 목록 (" << samples.size() << "건) --\n";
    if (samples.empty()) { std::cout << "  등록된 시료가 없습니다.\n"; return; }
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(20) << "이름"
              << std::setw(10) << "재고"
              << std::setw(8)  << "수율"
              << std::setw(12) << "사이클(h)"
              << "등록일시\n";
    std::cout << std::string(70, '-') << "\n";
    for (const auto& s : samples) printSample(s);
}

void SampleView::doSearchSample() {
    std::string keyword;
    std::cout << "검색 키워드 : "; std::getline(std::cin, keyword);
    auto results = ctrl_.searchByName(keyword);
    std::cout << "\n-- 검색 결과 (" << results.size() << "건) --\n";
    if (results.empty()) { std::cout << "  결과가 없습니다.\n"; return; }
    for (const auto& s : results) printSample(s);
}

void SampleView::printSample(const Sample& s) const {
    std::cout << std::left
              << std::setw(6)  << s.id
              << std::setw(20) << s.name
              << std::setw(10) << s.quantity
              << std::setw(8)  << s.yield
              << std::setw(12) << s.cycleTime
              << s.registeredAt << "\n";
}
