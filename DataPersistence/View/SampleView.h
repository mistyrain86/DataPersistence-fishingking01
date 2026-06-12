#pragma once
#include "../Controller/SampleController.h"

class SampleView {
public:
    explicit SampleView(SampleController& ctrl);
    void run();

private:
    void showMenu();
    void doAddSample();
    void doListSamples();
    void doSearchSample();
    void printSample(const Sample& s) const;

    SampleController& ctrl_;
};
