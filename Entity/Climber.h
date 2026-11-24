#pragma once

#include <string>
#include <vector>
#include "enums.h"

class AscentLog;

class Climber {
    int climberId;
    std::string fullName;
    Experience experience;
    int insuranceId;
    std::vector<int> ascentLogsIds;

public:
    Climber();

    Climber(int climberId, std::string fullName,
            Experience experience, int insuranceId,
            std::vector<int> ascentLogIds);

    ~Climber();

    int getClimberId() const;
    std::string getFullName() const;
    Experience getExperience() const;
    int getInsuranceId() const;
    std::vector<int> getAscentLogsIds() const;
    void addAscentId(int ascentId);

    bool operator<(const Climber& other) const;
};
