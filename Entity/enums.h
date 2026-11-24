
#ifndef UNTITLED1_ENUMS_H
#define UNTITLED1_ENUMS_H

#endif


#pragma once

enum Difficulty {
    UIAA_I = 1, UIAA_II, UIAA_III, UIAA_IV, UIAA_V, UIAA_VI,
    UIAA_VII, UIAA_VIII, UIAA_IX, UIAA_X, UIAA_XI, UIAA_XII
};

enum Experience {
    BEGINNER = 1, INTERMEDIATE, ADVANCED, EXPERT
};

enum class WeatherConditions {
    SUNNY, CLOUDY, RAINY, SNOWY, WINDY, FOGGY
};

#include <iostream>

inline std::ostream& operator<<(std::ostream& os,
                                WeatherConditions weather) {
    switch (static_cast<int>(weather)) {
        case 0: os << "Sunny"; break;
        case 1: os << "Cloudy"; break;
        case 2: os << "Rainy"; break;
        case 3: os << "Snowy"; break;
        case 4: os << "Windy"; break;
        case 5: os << "Foggy"; break;
        default: os << "Unknown"; break;
    }

    return os;
}