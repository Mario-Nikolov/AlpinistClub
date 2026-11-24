#include "AscentLog.h"

AscentLog::AscentLog()
    : weatherConditions(WeatherConditions::SUNNY) {
}
AscentLog::AscentLog(
    int id,
    const std::string& date,
    const ClimbingRoute& climbingRoute,
    WeatherConditions weatherConditions,
    const Group& group)
    : id(id),
      date(date),
      climbingRoute(climbingRoute),
      weatherConditions(weatherConditions),
      group(group) {
}

AscentLog::~AscentLog() = default;

void AscentLog::setId(int id) {
    this->id = id;
}

void AscentLog::setDate(std::string date) {
    this->date = date;
}

void AscentLog::setClimbingRoute(ClimbingRoute route) {
    this->climbingRoute = route;
}

void AscentLog::setWeatherConditions(
    WeatherConditions weatherConditions) {

    this->weatherConditions = weatherConditions;
}

void AscentLog::setGroup(Group group) {
    this->group = group;
}

std::string AscentLog::getDate() const {
    return date;
}

ClimbingRoute AscentLog::getClimbingRoute() const {
    return climbingRoute;
}

WeatherConditions AscentLog::getWeatherConditions() const {
    return weatherConditions;
}

Group AscentLog::getGroup() const {
    return group;
}

int AscentLog::getId() const {
    return id;
}
