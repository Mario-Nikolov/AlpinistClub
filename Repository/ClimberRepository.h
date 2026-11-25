#pragma once

#include <vector>
#include "Climber.h"

class ClimberRepository {
    std::vector<Climber> climbers;

public:
    ClimberRepository() = default;

    void addClimber(const Climber& climber);

    const Climber* findClimberById(int climberId) const;

    const std::vector<Climber>& getClimbers() const;

    void loadFromFile();

    void saveClimbersToFile() const;

    void addAscentToClimber(int climberId, int ascentId);
};
