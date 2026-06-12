#include <iostream>
#include <filesystem>
#include <Windows.h>

#include "Model/SampleRepository.h"
#include "Model/OrderRepository.h"

#include "Controller/SampleController.h"
#include "Controller/OrderController.h"
#include "Controller/DashboardController.h"
#include "Controller/ProductionController.h"
#include "Controller/ReleaseController.h"

#include "View/MainView.h"
#include "View/SampleView.h"
#include "View/OrderView.h"
#include "View/DashboardView.h"
#include "View/ProductionView.h"
#include "View/ReleaseView.h"

#include "Util/DummyDataGenerator.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::filesystem::create_directories("data");

    // Repository — JSON 파일 경로 주입, 생성자에서 자동 로드
    SampleRepository sampleRepo("data/samples.json");
    OrderRepository  orderRepo("data/orders.json");

    // 최초 실행 시에만 더미 데이터 생성
    if (sampleRepo.count() == 0 && orderRepo.count() == 0) {
        DummyDataGenerator gen(sampleRepo, orderRepo);
        gen.generate();
    }

    // Controller
    SampleController     sampleCtrl(sampleRepo);
    OrderController      orderCtrl(orderRepo, sampleRepo);
    DashboardController  dashboardCtrl(orderRepo, sampleRepo);
    ProductionController productionCtrl(orderRepo, sampleRepo);
    ReleaseController    releaseCtrl(orderRepo);

    // View
    SampleView     sampleView(sampleCtrl);
    OrderView      orderView(orderCtrl, sampleCtrl);
    DashboardView  dashboardView(dashboardCtrl);
    ProductionView productionView(productionCtrl);
    ReleaseView    releaseView(releaseCtrl);

    MainView mainView(sampleView, orderView, dashboardView,
                      productionView, releaseView);
    mainView.run();

    return 0;
}
