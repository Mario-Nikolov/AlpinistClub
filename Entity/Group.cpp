#include "Group.h"
#include <stdexcept>

Group::Group() = default;

Group::Group(Climber leader, std::set<Climber> climbers)
    : leader(leader), climbers(climbers) {

    if (climbers.empty()) {
        throw std::invalid_argument("No climbers found.");
    }
}

Group::~Group() = default;

Climber Group::getLeader() const {
    return leader;
}

std::set<Climber> Group::getClimbers() const {
    return climbers;
}
