#pragma once
#include <vector>
#include <optional>
#include <string>
#include "Sample.h"

class SampleRepository {
public:
    explicit SampleRepository(std::string filePath = "");

    void                     add(const Sample& sample);
    std::optional<Sample>    findById(const std::string& id) const;
    std::vector<Sample>      findAll() const;
    std::vector<Sample>      findByName(const std::string& keyword) const;
    bool                     update(const Sample& sample);
    bool                     remove(const std::string& id);
    int                      count() const;

private:
    void load();
    void save() const;

    std::vector<Sample> samples_;
    std::string         filePath_;
};
