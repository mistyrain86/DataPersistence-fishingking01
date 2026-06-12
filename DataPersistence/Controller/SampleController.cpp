#include "SampleController.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

int SampleController::idCounter_ = 0;

namespace {
    std::string currentTimeStr() {
        auto now = std::chrono::system_clock::now();
        auto t   = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
        localtime_s(&tm, &t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
}

SampleController::SampleController(SampleRepository& sampleRepo)
    : sampleRepo_(sampleRepo) {}

bool SampleController::addSample(const std::string& name, int quantity,
                                  double yield, double cycleTime) {
    Sample s;
    s.id           = "S" + std::to_string(++idCounter_);
    s.name         = name;
    s.quantity     = quantity;
    s.yield        = yield;
    s.cycleTime    = cycleTime;
    s.registeredAt = currentTimeStr();
    sampleRepo_.add(s);
    return true;
}

std::vector<Sample> SampleController::getAllSamples() const {
    return sampleRepo_.findAll();
}

std::optional<Sample> SampleController::getSampleById(const std::string& id) const {
    return sampleRepo_.findById(id);
}

std::vector<Sample> SampleController::searchByName(const std::string& keyword) const {
    return sampleRepo_.findByName(keyword);
}
