//
// Created by mario on 11/11/2026.
//

#ifndef UNTITLED1_CLIMBINGROUTE_H
#define UNTITLED1_CLIMBINGROUTE_H

#endif //UNTITLED1_CLIMBINGROUTE_H


#pragma once

#include <string>
#include <vector>
#include "enums.h"

class ClimbingRoute {
    std::string name;
    std::string mountain;
    int altitude;
    Difficulty difficulty;
    double estimatedDuration;
    std::vector<std::string> requiredEquipment;
    std::string region;

public:
    ClimbingRoute();

    ClimbingRoute(std::string name,
                  std::string mountain,
                  int altitude,
                  Difficulty difficulty,
                  double estimatedDuration,
                  std::vector<std::string> requiredEquipment,
                  std::string region);

    std::string getName() const;
    std::string getMountain() const;
    int getAltitude() const;
    Difficulty getDifficulty() const;
    double getEstimatedDuration() const;
    std::vector<std::string> getRequiredEquipment() const;
    std::string getRegion() const;
};

