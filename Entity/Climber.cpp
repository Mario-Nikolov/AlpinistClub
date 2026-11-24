#include "Climber.h"
#include <iostream>

Climber::Climber()
    : climberId(0), experience(BEGINNER), insuranceId(0) {
}

Climber::Climber(int climberId, std::string fullName,
                 Experience experience, int insuranceId,
                 std::vector<int> ascentLogIds) {

    if (climberId > 0) {
        this->climberId = climberId;
    } else {
        std::cout << "The climber must be greater than 0." << std::endl;
    }

    if (fullName.empty()) {
        std::cout << "A name required." << std::endl;
    } else {
        this->fullName = fullName;
    }

    this->experience = experience;

    if (insuranceId > 0) {
        this->insuranceId = insuranceId;
    } else {
        std::cout << "The insurance must be greater than 0." << std::endl;
    }

    this->ascentLogsIds = ascentLogIds;
}

Climber::~Climber() = default;

int Climber::getClimberId() const {
    return climberId;
}

std::string Climber::getFullName() const {
    return fullName;
}

Experience Climber::getExperience() const {
    return experience;
}

int Climber::getInsuranceId() const {
    return insuranceId;
}

std::vector<int> Climber::getAscentLogsIds() const {
    return ascentLogsIds;
}

bool Climber::operator<(const Climber& other) const {
    return climberId < other.climberId;
}

void Climber::addAscentId(int ascentId) {
    ascentLogsIds.push_back(ascentId);
}
