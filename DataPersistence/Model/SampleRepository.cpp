#include "SampleRepository.h"
#include <algorithm>
#include <fstream>
#include "../Util/json.hpp"

using json = nlohmann::json;

static json sampleToJson(const Sample& s) {
    return {
        {"id",           s.id},
        {"name",         s.name},
        {"quantity",     s.quantity},
        {"yield",        s.yield},
        {"cycleTime",    s.cycleTime},
        {"registeredAt", s.registeredAt}
    };
}

static Sample sampleFromJson(const json& j) {
    Sample s;
    s.id           = j.at("id").get<std::string>();
    s.name         = j.at("name").get<std::string>();
    s.quantity     = j.at("quantity").get<int>();
    s.yield        = j.at("yield").get<double>();
    s.cycleTime    = j.at("cycleTime").get<double>();
    s.registeredAt = j.at("registeredAt").get<std::string>();
    return s;
}

SampleRepository::SampleRepository(std::string filePath)
    : filePath_(std::move(filePath))
{
    if (!filePath_.empty())
        load();
}

void SampleRepository::add(const Sample& sample) {
    samples_.push_back(sample);
    save();
}

std::optional<Sample> SampleRepository::findById(const std::string& id) const {
    for (const auto& s : samples_)
        if (s.id == id) return s;
    return std::nullopt;
}

std::vector<Sample> SampleRepository::findAll() const {
    return samples_;
}

std::vector<Sample> SampleRepository::findByName(const std::string& keyword) const {
    std::vector<Sample> result;
    for (const auto& s : samples_)
        if (s.name.find(keyword) != std::string::npos)
            result.push_back(s);
    return result;
}

bool SampleRepository::update(const Sample& sample) {
    for (auto& s : samples_) {
        if (s.id == sample.id) { s = sample; save(); return true; }
    }
    return false;
}

bool SampleRepository::remove(const std::string& id) {
    auto it = std::find_if(samples_.begin(), samples_.end(),
        [&id](const Sample& s) { return s.id == id; });
    if (it == samples_.end()) return false;
    samples_.erase(it);
    save();
    return true;
}

int SampleRepository::count() const {
    return static_cast<int>(samples_.size());
}

void SampleRepository::load() {
    std::ifstream f(filePath_);
    if (!f.is_open()) return;
    try {
        json j = json::parse(f);
        for (const auto& item : j)
            samples_.push_back(sampleFromJson(item));
    } catch (...) {}
}

void SampleRepository::save() const {
    if (filePath_.empty()) return;
    json j = json::array();
    for (const auto& s : samples_)
        j.push_back(sampleToJson(s));
    std::ofstream f(filePath_);
    if (f.is_open())
        f << j.dump(2);
}
