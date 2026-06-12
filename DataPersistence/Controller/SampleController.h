#pragma once
#include <string>
#include <vector>
#include <optional>
#include "../Model/Sample.h"
#include "../Model/SampleRepository.h"

class SampleController {
public:
    explicit SampleController(SampleRepository& sampleRepo);

    bool                  addSample(const std::string& name, int quantity,
                                    double yield, double cycleTime);
    std::vector<Sample>   getAllSamples() const;
    std::optional<Sample> getSampleById(const std::string& id) const;
    std::vector<Sample>   searchByName(const std::string& keyword) const;

private:
    SampleRepository& sampleRepo_;
    static int        idCounter_;
};
