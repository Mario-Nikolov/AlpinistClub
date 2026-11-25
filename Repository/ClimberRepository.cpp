#include "ClimberRepository.h"
#include <fstream>
#include <sstream>
#include "ClimberIdAlreadyExistsException.h"
#include "CouldNotOpenFileException.h"
#include "CouldNotSaveClimberException.h"
#include "FileUtils.h"
#include "InvalidExperienceException.h"
#include "FileUtils.h"

const Climber* ClimberRepository::findClimberById(int climberId) const {
    for (const Climber& climber : climbers) {
        if (climber.getClimberId() == climberId) {
            return &climber;
        }
    }

    return nullptr;
}

const std::vector<Climber>& ClimberRepository::getClimbers() const {
    return climbers;
}

void ClimberRepository::addClimber(const Climber& climber) {
    for (const Climber& existing : climbers) {
        if (existing.getClimberId() == climber.getClimberId()) {
            throw ClimberIdAlreadyExistsException();
        }
    }

    std::ofstream file("climbers.csv", std::ios::app);

    if (!file.is_open()) {
        throw CouldNotOpenFileException("climbers.csv");
    }

    std::stringstream ss;

    ss << climber.getClimberId() << ","
       << climber.getFullName() << ","
       << climber.getExperience() << ","
       << climber.getInsuranceId();

    for (int ascentId : climber.getAscentLogsIds()) {
        ss << "," << ascentId;
    }

    file << ss.str() << "\n";
    file.flush();

    if (!file) {
        throw CouldNotSaveClimberException();
    }

    climbers.push_back(climber);
}

void ClimberRepository::saveClimbersToFile() const {
    std::ofstream file("climbers.csv", std::ios::trunc);

    if (!file.is_open()) {
        throw CouldNotOpenFileException("climbers.csv");
    }

    for (const Climber& climber : climbers) {
        file << climber.getClimberId() << ","
             << climber.getFullName() << ","
             << climber.getExperience() << ","
             << climber.getInsuranceId();

        for (int ascentId : climber.getAscentLogsIds()) {
            file << "," << ascentId;
        }

        file << "\n";
    }

    file.close();

    if (!file) {
        throw CouldNotSaveClimberException();
    }
}

void ClimberRepository::loadFromFile() {
    climbers.clear();

    std::ifstream climbersFile("climbers.csv");
    std::string line;

    if (climbersFile.is_open()) {
        while (std::getline(climbersFile, line)) {
            if (line.empty()) {
                continue;
            }

            std::stringstream ss(line);

            int id = std::stoi(readField(ss, ','));
            std::string name = readField(ss, ',');
            int experience = std::stoi(readField(ss, ','));
            int insurance = std::stoi(readField(ss, ','));

            if (experience < 1 || experience > 4) {
                throw InvalidExperienceException();
            }

            std::vector<int> ascentsIds;
            std::string ascentId;

            while (std::getline(ss, ascentId, ',')) {
                if (ascentId.empty()) {
                    continue;
                }

                ascentsIds.push_back(std::stoi(ascentId));
            }

            climbers.emplace_back(
                id,
                name,
                static_cast<Experience>(experience),
                insurance,
                ascentsIds
            );
        }
    }
}
void ClimberRepository::addAscentToClimber(int climberId, int ascentId) {
    for (Climber& climber : climbers) {
        if (climber.getClimberId() == climberId) {
            climber.addAscentId(ascentId);
            return;
        }
    }

    throw std::runtime_error("Climber not found");
}
