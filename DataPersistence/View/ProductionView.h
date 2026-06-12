#pragma once
#include "../Controller/ProductionController.h"

class ProductionView {
public:
    explicit ProductionView(ProductionController& ctrl);
    void run();

private:
    void showMenu();
    void doShowQueue();
    void doCompleteProduction();

    ProductionController& ctrl_;
};
