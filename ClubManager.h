#pragma once

#include <vector>
#include <deque>
#include <string>
#include "Entity/AscentLog.h"
#include "Entity/ClimbingRoute.h"
#include "Entity/Insurance.h"
#include "Entity/Climber.h"

class ClubManager {
    std::vector<ClimbingRoute> routes;
    std::vector<Climber> climbers;
    std::deque<AscentLog> storedAscents;
    std::vector<Insurance> insurances;

public:
    ClubManager();

    ClubManager(const std::vector<ClimbingRoute>& routes,
                const std::vector<Climber>& climbers,
                const std::deque<AscentLog>& storedAscents,
                const std::vector<Insurance>& insurances);

    void addRoute(const ClimbingRoute& route);
    void addClimber(const Climber& climber);
    void addInsurance(const Insurance& insurance);

    void loadData();

    void printClimber( const Climber& climber) const ;
    void printClimbers() const;

    void printRoute( const ClimbingRoute& route) const;
    void printRoutes() const;

    void showClimberInfo(const Climber& climber) const;

    void printAscentById(int id) const;
    
    void saveClimbersToFile() const;

    const ClimbingRoute* findRouteByName(const std::string& name) const;

    const AscentLog* findAscentById(int id) const;

    const Climber* findClimberById(int climberId) const;

    bool checkExperience(Experience experience,
                         Difficulty difficulty) const;

    bool checkInsurance(int insuranceId,
                        const std::string& climbingDate) const;

    bool ascentExists(int id) const;

    Insurance checkInsurance(int insuranceId) const;

    void registerClimb(const ClimbingRoute& route,
                       const Climber& climber);

    const std::vector<ClimbingRoute>& getRoutes() const;
    const std::vector<Climber>& getClimbers() const;
    const std::vector<Insurance>& getInsurances() const;
    const std::deque<AscentLog>& getStoredAscents() const;
};
