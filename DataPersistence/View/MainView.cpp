#include "MainView.h"
#include <iostream>
#include <limits>

MainView::MainView(SampleView& sampleView, OrderView& orderView,
                   DashboardView& dashboardView, ProductionView& productionView,
                   ReleaseView& releaseView)
    : sampleView_(sampleView), orderView_(orderView),
      dashboardView_(dashboardView), productionView_(productionView),
      releaseView_(releaseView) {}

void MainView::showMenu() {
    std::cout << "\n====================================\n";
    std::cout << "  반도체 시료 주문관리 시스템 (S-Semi)\n";
    std::cout << "====================================\n";
    std::cout << "  1. 시료 관리\n";
    std::cout << "  2. 주문 관리\n";
    std::cout << "  3. 대시보드\n";
    std::cout << "  4. 생산 관리\n";
    std::cout << "  5. 출고 처리\n";
    std::cout << "  0. 종료\n";
    std::cout << "====================================\n";
    std::cout << "선택 > ";
}

void MainView::run() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case 1: sampleView_.run();     break;
        case 2: orderView_.run();      break;
        case 3: dashboardView_.run();  break;
        case 4: productionView_.run(); break;
        case 5: releaseView_.run();    break;
        case 0:
            std::cout << "\n시스템을 종료합니다.\n"; break;
        default:
            std::cout << "[오류] 잘못된 입력입니다.\n";
        }
    }
}
