#include "ClubManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "Exceptions/ClimberIdAlreadyExistsException.h"
#include "Exceptions/CouldNotOpenFileException.h"
#include "Exceptions/CouldNotSaveClimberException.h"
#include "Exceptions/CouldNotSaveInsuranceException.h"
#include "Exceptions/CouldNotSaveRouteException.h"
#include "Exceptions/DuplicateInsuranceIdInFileException.h"
#include "Exceptions/GroupExceptions.h"
#include "Exceptions/InsufficientExperienceException.h"
#include "Exceptions/InsuranceAlreadyExistsException.h"
#include "Exceptions/InsuranceNotFoundException.h"
#include "Exceptions/InvalidAscentException.h"
#include "Exceptions/InvalidDifficultyException.h"
#include "Exceptions/InvalidExperienceException.h"
#include "Exceptions/InvalidFileDataException.h"
#include "Exceptions/InvalidInsuranceDataException.h"
#include "Exceptions/InvalidInsuranceException.h"
#include "Exceptions/InvalidWeatherException.h"
#include "FileUtils.h"

ClubManager::ClubManager() = default;

ClubManager::ClubManager(
    const std::vector<ClimbingRoute>& routes,
    const ClimberRepository& climberRepository,
    const std::deque<AscentLog>& storedAscents,
    const std::vector<Insurance>& insurances
    ):
    routes(routes),
    climberRepository(climberRepository),
    storedAscents(storedAscents),
    insurances(insurances){}

const std::vector<ClimbingRoute>& ClubManager::getRoutes() const {
    return routes;
}

const std::vector<Climber>& ClubManager::getClimbers() const {
    return climberRepository.getClimbers();
}

const std::deque<AscentLog>& ClubManager::getStoredAscents() const {
    return storedAscents;
}

const std::vector<Insurance>& ClubManager::getInsurances() const {
    return insurances;
}

bool ClubManager::ascentExists(int id) const {
    for (const AscentLog& ascent : storedAscents) {
        if (ascent.getId() == id) {
            return true;
        }
    }

    return false;
}

void ClubManager::addRoute(const ClimbingRoute& route) {
    std::ofstream file("routes.csv", std::ios::app);

    if (!file.is_open()) {
        throw CouldNotOpenFileException("routes.csv");
    }

    file << route.getName() << ","
         << route.getMountain() << ","
         << route.getAltitude() << ","
         << route.getDifficulty() << ","
         << route.getEstimatedDuration() << ","
         << route.getRegion();

    for (const std::string& item : route.getRequiredEquipment()) {
        file << "," << item;
    }

    file << "\n";
    file.flush();

    if (!file) {
        throw CouldNotSaveRouteException();
    }

    routes.push_back(route);

    std::cout << "The route " << route.getName()
              << " was saved!" << std::endl;
}

void ClubManager::addClimber(const Climber& climber) {
    climberRepository.addClimber(climber);

    std::cout << "The climber was saved!" << std::endl;
}

void ClubManager::addInsurance(const Insurance& insurance) {
    for (const Insurance& existing : insurances) {
        if (existing.getInsuranceId() == insurance.getInsuranceId()) {
            throw InsuranceAlreadyExistsException();
        }
    }

    std::ofstream file("insurances.csv", std::ios::app);

    if (!file.is_open()) {
        throw CouldNotOpenFileException("insurances.csv");
    }

    file << insurance.getInsuranceId() << ","
         << insurance.getStartDate() << ","
         << insurance.getExpiryDate() << "\n";

    file.flush();

    if (!file) {
        throw CouldNotSaveInsuranceException();
    }

    insurances.push_back(insurance);

    std::cout << "The insurance was saved!" << std::endl;
}

void ClubManager::loadData() {
    routes.clear();
    storedAscents.clear();
    insurances.clear();

    std::ifstream routesFile("routes.csv");
    std::string line;

    if (routesFile.is_open()) {
        while (std::getline(routesFile, line)) {
            if (line.empty()) {
                continue;
            }

            std::stringstream ss(line);

            std::string name = readField(ss, ',');
            std::string mountain = readField(ss, ',');
            int altitude = std::stoi(readField(ss, ','));
            int difficulty = std::stoi(readField(ss, ','));
            double duration = std::stod(readField(ss, ','));
            std::string region = readField(ss, ',');

            if (difficulty < 1 || difficulty > 12) {
                throw InvalidDifficultyException();
            }

            std::vector<std::string> equipment;
            std::string item;

            while (std::getline(ss, item, ',')) {
                if (!item.empty()) {
                    equipment.push_back(item);
                }
            }

            routes.emplace_back(
                name,
                mountain,
                altitude,
                static_cast<Difficulty>(difficulty),
                duration,
                equipment,
                region
            );
        }
    }

    climberRepository.loadFromFile();


    std::ifstream insuranceFile("insurances.csv");

    if (insuranceFile.is_open()) {
        while (std::getline(insuranceFile, line)) {
            if (line.empty()) {
                continue;
            }

            std::stringstream ss(line);

            std::string id = readField(ss, ',');
            std::string startDate = readField(ss, ',');

            std::string expiryDate;

            if (!std::getline(ss, expiryDate, ',') || expiryDate.empty()) {
                throw InvalidInsuranceDataException();
            }

            Insurance insurance(
                std::stoi(id),
                startDate,
                expiryDate
            );

            for (const Insurance& existing : insurances) {
                if (existing.getInsuranceId() == insurance.getInsuranceId()) {
                    throw DuplicateInsuranceIdInFileException();
                }
            }

            insurances.push_back(insurance);
        }
    }

    std::ifstream ascentsFile("ascents.csv");

    if (ascentsFile.is_open()) {
        while (std::getline(ascentsFile, line)) {

            if (line.empty()) {
                continue;
            }

            std::stringstream ss(line);

            int id = std::stoi(readField(ss, ','));

            std::string date = readField(ss, ',');

            std::string routeName = readField(ss, ',');

            const ClimbingRoute* route = findRouteByName(routeName);

            if (route == nullptr) {
                throw std::runtime_error("Route not found");
            }

            int weather = std::stoi(readField(ss, ','));

            if (weather < 0 || weather > 5) {
                throw InvalidWeatherException();
            }

            WeatherConditions weatherConditions =
                static_cast<WeatherConditions>(weather);

            int leaderId = std::stoi(readField(ss, ','));

            const Climber* leader = findClimberById(leaderId);

            if (leader == nullptr) {
                throw std::runtime_error("Leader not found");
            }

            std::string climberData;

            std::set<Climber> groupClimbers;

            while (std::getline(ss, climberData, ',')) {

                if (climberData.empty()) {
                    continue;
                }

                int climberId = std::stoi(climberData);

                const Climber* climber = findClimberById(climberId);

                if (climber == nullptr) {
                    throw std::runtime_error("Climber not found");
                }

                groupClimbers.insert(*climber);
            }

            Group group(*leader, groupClimbers);

            AscentLog ascentLog;

            ascentLog.setId(id);
            ascentLog.setDate(date);
            ascentLog.setClimbingRoute(*route);
            ascentLog.setWeatherConditions(weatherConditions);
            ascentLog.setGroup(group);

            storedAscents.push_back(ascentLog);
        }

        ascentsFile.close();
    }
}

void ClubManager::printClimber( const Climber& climber) const {
    std::cout << "ID: " << climber.getClimberId() << "\n"
                  << "Name: " << climber.getFullName() << "\n"
                  << "Experience: " << climber.getExperience() << "\n"
                  << "Insurance ID: " << climber.getInsuranceId() << "\n"
                  << "Insurance start date: " << checkInsurance(climber.getInsuranceId()).getStartDate() << "\n"
                  << "Insurance expiry date: " << checkInsurance(climber.getInsuranceId()).getExpiryDate() << "\n"
                  << "------------------------\n";
}

void ClubManager::printClimbers() const {
    if (climberRepository.getClimbers().empty()) {
        std::cout << "No climbers found!\n";
        return;
    }

    for (const Climber& climber : climberRepository.getClimbers()) {
        printClimber(climber);
    }
}

void ClubManager::printRoute( const ClimbingRoute& route) const {
    std::cout << "\nPeak: " << route.getName() << "\n";
    std::cout << "Mountain: " << route.getMountain() << "\n";
    std::cout << "Altitude: " << route.getAltitude() << " m\n";
    std::cout << "Difficulty: UIAA " << route.getDifficulty() << "\n";
    std::cout << "Duration: " << route.getEstimatedDuration() << " hours\n";
    std::cout << "Region: " << route.getRegion() << "\n";
    std::cout << "Equipment: ";

    std::vector<std::string> equipment = route.getRequiredEquipment();

    if (equipment.empty()) {
        std::cout << "None";
    }

    for (size_t i = 0; i < equipment.size(); i++) {
        std::cout << equipment[i];

        if (i + 1 < equipment.size()) {
            std::cout << ", ";
        }
    }

    std::cout << "\n----------------------------------------\n";
}
void ClubManager::printRoutes() const {
    if (routes.empty()) {
        std::cout << "No routes found!\n";
        return;
    }
    for (const ClimbingRoute& route : routes) {
        printRoute(route);
    }
}

const Climber* ClubManager::findClimberById(int id) const {
    return climberRepository.findClimberById(id);
}

void ClubManager::printAscentById(int id) const {
    const AscentLog* ascent = findAscentById(id);

    if (ascent == nullptr) {
        std::cout << "Ascent with ID " << id << " not found!\n";
        return;
    }

    std::cout << "Ascent ID: " << ascent->getId() << "\n";
    std::cout << "Date: " << ascent->getDate() << "\n";
    std::cout << "Route: " << ascent->getClimbingRoute().getName() << "\n";
    std::cout << "Mountain: " << ascent->getClimbingRoute().getMountain() << "\n";
    std::cout << "Weather: " << ascent->getWeatherConditions() << "\n";

    Group group = ascent->getGroup();

    std::cout << "Group leader: "
              << group.getLeader().getFullName() << "\n";

    std::cout << "Group members:\n";

    for (const Climber& member : group.getClimbers()) {
        std::cout << " - " << member.getFullName() << "\n";
    }

    std::cout << "-------------------------\n";
}

const AscentLog* ClubManager::findAscentById(int id) const {
    for (const AscentLog& ascent : storedAscents) {
        if (ascent.getId() == id) {
            return &ascent;
        }
    }

    return nullptr;
}

void ClubManager::showClimberInfo(const Climber& climber) const {
    if (climberRepository.getClimbers().empty()) {
        std::cout << "No climbers found!\n";
        return;
    }

    printClimber(climber);

    if (climber.getAscentLogsIds().empty()) {
        std::cout << "No ascents found!\n";
        return;
    }

    std::cout << "\n======== Ascents ========\n";

    for (int ascentId : climber.getAscentLogsIds()) {
        printAscentById(ascentId);
    }
}
bool ClubManager::checkExperience(
    Experience experience,
    Difficulty difficulty) const {

    if ((experience == BEGINNER && difficulty <= UIAA_III) ||
        (experience == INTERMEDIATE && difficulty <= UIAA_VI) ||
        (experience == ADVANCED && difficulty <= UIAA_IX) ||
        (experience == EXPERT && difficulty <= UIAA_XII)) {
        return true;
    }

    return false;
}

bool ClubManager::checkInsurance(
    int insuranceId,
    const std::string& climbingDate) const {

    for (const Insurance& insurance : insurances) {
        if (insurance.getInsuranceId() == insuranceId) {
            return insurance.isValid(climbingDate);
        }
    }

    return false;
}

const ClimbingRoute* ClubManager::findRouteByName(
    const std::string& name) const {

    for (const ClimbingRoute& route : routes) {

        if (route.getName() == name) {
            return &route;
        }
    }

    return nullptr;
}

Insurance ClubManager::checkInsurance(int insuranceId) const {

    for (const Insurance& insurance : insurances) {
        if (insurance.getInsuranceId() == insuranceId) {
            return insurance;
        }
    }

    throw InsuranceNotFoundException();
}

void ClubManager::saveClimbersToFile() const {
    climberRepository.saveClimbersToFile();
}

void ClubManager::registerClimb(
    const ClimbingRoute& route,
    const Climber& climber) {

    if (!checkExperience(
            climber.getExperience(),
            route.getDifficulty())) {
        throw InsufficientExperienceException();
    }

    std::string date;

    std::cout << "Date (DD-MM-YYYY): ";
    std::cin >> date;

    if (!checkInsurance(climber.getInsuranceId(), date)) {
        throw InvalidInsuranceException();
    }

    AscentLog ascentLog;
    ascentLog.setDate(date);
    ascentLog.setClimbingRoute(route);

    int weatherInput;

    std::cout << "Weather conditions:\n";
    std::cout << "1. Sunny\n";
    std::cout << "2. Cloudy\n";
    std::cout << "3. Rainy\n";
    std::cout << "4. Snowy\n";
    std::cout << "5. Windy\n";
    std::cout << "6. Foggy\n";

    std::cout << "Choose: ";
    std::cin >> weatherInput;

    if (!std::cin || weatherInput < 1 || weatherInput > 6) {
        throw InvalidWeatherException();
    }

    WeatherConditions weather =
        static_cast<WeatherConditions>(weatherInput - 1);

    ascentLog.setWeatherConditions(weather);

    std::set<Climber> groupClimbers;
    groupClimbers.insert(climber);

    int membersCount;

    std::cout << "Number of additional climbers: ";
    std::cin >> membersCount;

    if (!std::cin || membersCount < 0) {
        throw std::runtime_error("Invalid members count");
    }

    for (int i = 0; i < membersCount; i++) {

        int climberId;

        std::cout << "Climber ID: ";
        std::cin >> climberId;

        if (!std::cin) {
            throw std::runtime_error("Invalid climber ID");
        }

        const Climber* member = findClimberById(climberId);

        if (member == nullptr) {
            throw std::runtime_error("Climber not found");
        }

        if (!checkExperience(
                member->getExperience(),
                route.getDifficulty())) {
            throw InsufficientExperienceException();
        }

        if (!checkInsurance(member->getInsuranceId(), date)) {
            throw InvalidInsuranceException();
        }

        if (!groupClimbers.insert(*member).second) {
            throw std::runtime_error("Duplicate climber");
        }
    }

    Group group(climber, groupClimbers);

    ascentLog.setGroup(group);

    int id = 1;

    for (const AscentLog& ascent : storedAscents) {
        if (ascent.getId() >= id) {
            id = ascent.getId() + 1;
        }
    }

    ascentLog.setId(id);

    std::ofstream file("ascents.csv", std::ios::app);

    if (!file.is_open()) {
        throw CouldNotOpenFileException("ascents.csv");
    }

    file << ascentLog.getId() << ","
         << ascentLog.getDate() << ","
         << route.getName() << ","
         << static_cast<int>(weather) << ","
         << climber.getClimberId();

    for (const Climber& member : groupClimbers) {
        file << "," << member.getClimberId();
    }

    file << "\n";
    file.close();

    if (!file) {
        throw std::runtime_error("Could not save ascent");
    }

    storedAscents.push_back(ascentLog);

    saveClimbersToFile();

    std::cout << "Ascent registered successfully!\n";
}

