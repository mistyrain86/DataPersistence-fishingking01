#pragma once
#include "../Controller/DashboardController.h"

class DashboardView {
public:
    explicit DashboardView(DashboardController& ctrl);
    void run();

private:
    void showMenu();
    void doShowOrderStatus();
    void doShowSampleStatus();

    DashboardController& ctrl_;
};
