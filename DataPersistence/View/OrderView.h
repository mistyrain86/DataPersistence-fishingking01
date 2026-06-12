#pragma once
#include "../Controller/OrderController.h"
#include "../Controller/SampleController.h"

class OrderView {
public:
    OrderView(OrderController& orderCtrl, SampleController& sampleCtrl);
    void run();

private:
    void showMenu();
    void doReserveOrder();
    void doListAllOrders();
    void doListReservedOrders();
    void doApproveOrReject();
    void printOrder(const Order& o) const;

    OrderController&  orderCtrl_;
    SampleController& sampleCtrl_;
};
