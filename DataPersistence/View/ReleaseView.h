#pragma once
#include "../Controller/ReleaseController.h"

class ReleaseView {
public:
    explicit ReleaseView(ReleaseController& ctrl);
    void run();

private:
    void showMenu();
    void doListConfirmed();
    void doRelease();
    void printOrder(const Order& o) const;

    ReleaseController& ctrl_;
};
