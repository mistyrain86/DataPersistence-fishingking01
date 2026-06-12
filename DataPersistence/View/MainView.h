#pragma once
#include "SampleView.h"
#include "OrderView.h"
#include "DashboardView.h"
#include "ProductionView.h"
#include "ReleaseView.h"

class MainView {
public:
    MainView(SampleView& sampleView, OrderView& orderView,
             DashboardView& dashboardView, ProductionView& productionView,
             ReleaseView& releaseView);
    void run();

private:
    void showMenu();

    SampleView&     sampleView_;
    OrderView&      orderView_;
    DashboardView&  dashboardView_;
    ProductionView& productionView_;
    ReleaseView&    releaseView_;
};
