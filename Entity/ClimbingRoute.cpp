#include "ClimbingRoute.h"
#include <stdexcept>

ClimbingRoute::ClimbingRoute()
    : altitude(0),
      difficulty(UIAA_I),
      estimatedDuration(0) {
}

ClimbingRoute::ClimbingRoute(std::string name,std::string mountain,int altitude,
    Difficulty difficulty,double estimatedDuration,std::vector<std::string> requiredEquipment,std::string region):

        name(name),mountain(mountain),altitude(altitude),
      difficulty(difficulty),estimatedDuration(estimatedDuration),requiredEquipment(requiredEquipment),region(region) {

    if (altitude <= 0) {
        throw std::invalid_argument("Altitude must be positive");
    }

    if (estimatedDuration <= 0) {
        throw std::invalid_argument("Duration must be positive");
    }
}

std::string ClimbingRoute::getName() const {
    return name;
}

std::string ClimbingRoute::getMountain() const {
    return mountain;
}

int ClimbingRoute::getAltitude() const {
    return altitude;
}

Difficulty ClimbingRoute::getDifficulty() const {
    return difficulty;
}

double ClimbingRoute::getEstimatedDuration() const {
    return estimatedDuration;
}

std::vector<std::string> ClimbingRoute::getRequiredEquipment() const {
    return requiredEquipment;
}

std::string ClimbingRoute::getRegion() const {
    return region;
}

