#ifndef UNTITLED1_ASCENTLOG_H
#define UNTITLED1_ASCENTLOG_H

#endif //UNTITLED1_ASCENTLOG_H

#pragma once

#include <string>
#include "ClimbingRoute.h"
#include "Group.h"
#include "enums.h"

class AscentLog {
    int id;
    std::string date;
    ClimbingRoute climbingRoute;
    WeatherConditions weatherConditions;
    Group group;

public:
    AscentLog();
    AscentLog(int id,
          const std::string& date,
          const ClimbingRoute& climbingRoute,
          WeatherConditions weatherConditions,
          const Group& group);
    ~AscentLog();

    void setId(int id);
    void setDate(std::string date);
    void setClimbingRoute(ClimbingRoute route);
    void setWeatherConditions(WeatherConditions weatherConditions);
    void setGroup(Group group);

    std::string getDate() const;
    ClimbingRoute getClimbingRoute() const;
    WeatherConditions getWeatherConditions() const;
    Group getGroup() const;
    int getId() const;
};

