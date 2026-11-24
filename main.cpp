#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "ClubManager.h"
#include "Exceptions/InputExceptions.h"

std::string readText(const std::string& message) {
    while (true) {
        try {
            std::string value;

            std::cout << message;

            if (!std::getline(std::cin, value)) {
                throw std::runtime_error("Input error!");
            }

            if (value.find_first_not_of(" \t") == std::string::npos) {
                throw EmptyFieldException();
            }

            if (value.find_first_of(",;|~") != std::string::npos) {
                throw InvalidCharacterException();
            }

            return value;
        }
        catch (const EmptyFieldException& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
        catch (const InvalidCharacterException& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
}


std::string readDate(const std::string& message) {
    while (true) {
        std::string date = readText(message);

        try {
            if (date.size() != 10 ||
                date[2] != '-' || date[5] != '-') {
                throw InvalidDateFormatException();
                }

            int day = std::stoi(date.substr(0, 2));
            int month = std::stoi(date.substr(3, 2));
            int year = std::stoi(date.substr(6, 4));

            for (int i : {0, 1, 3, 4, 6, 7, 8, 9}) {
                if (date[i] < '0' || date[i] > '9') {
                    throw InvalidDateFormatException();
                }
            }

            bool leapYear = (year % 400 == 0) ||
                            (year % 4 == 0 && year % 100 != 0);

            int daysInMonth[] = {
                31, leapYear ? 29 : 28, 31, 30,
                31, 30, 31, 31, 30, 31, 30, 31
            };

            if (year < 1 || month < 1 || month > 12 ||
                day < 1 || day > daysInMonth[month - 1]) {
                throw InvalidCalendarDateException();
                }

            return date;

        } catch (const InvalidDateFormatException& e) {
            std::cout << "Error: " << e.what() << "\n";
            std::cout << "Please try again.\n\n";
        }
        catch (const InvalidCalendarDateException& e) {
            std::cout << "Error: " << e.what() << "\n";
            std::cout << "Please try again.\n\n";
        }
    }
}


int readInt(const std::string& message, int min, int max) {
    while (true) {
        try {
            std::string input = readText(message);
            std::stringstream ss(input);

            int value;
            char extra;

            if (!(ss >> value) || (ss >> extra)) {
                throw InvalidNumberException();
            }

            if (value < min || value > max) {
                throw ValueOutOfRangeException();
            }

            return value;

        } catch (const InvalidNumberException& e) {
            std::cout << "Error: " << e.what() << "\n";
            std::cout << "Please try again.\n\n";

        } catch (const ValueOutOfRangeException& e) {
            std::cout << "Error: " << e.what() << "\n";
            std::cout << "Allowed range: " << min
                      << " - " << max << "\n\n";
        }
    }
}

double readDouble(const std::string& message,
                  double min, double max) {

    while (true) {
        try {
            std::string input = readText(message);
            std::stringstream ss(input);

            double value;
            char extra;

            if (!(ss >> value) || (ss >> extra)) {
                throw InvalidNumberException();
            }

            if (!std::isfinite(value) || value < min || value > max) {
                throw ValueOutOfRangeException();
            }

            return value;

        } catch (const InvalidNumberException& e) {
            std::cout << "Error: " << e.what() << "\n";
            std::cout << "Please try again.\n\n";

        } catch (const ValueOutOfRangeException& e) {
            std::cout << "Error: " << e.what() << "\n";
            std::cout << "Allowed range: " << min
                      << " - " << max << "\n\n";
        }
    }
}

void printMenu() {
    std::cout << "\n========================================\n";
    std::cout << "          ALPINIST CLUB MANAGER\n";
    std::cout << "========================================\n\n";

    std::cout << "1. Add climbing route\n";
    std::cout << "2. Add climber\n";
    std::cout << "3. Register climb\n";
    std::cout << "4. Show all routes\n";
    std::cout << "5. Show all climbers\n";
    std::cout << "6. Show climber info\n";
    std::cout << "7. Filter routes by difficulty\n";
    std::cout << "8. Filter routes by mountain\n";
    std::cout << "0. Exit\n";

    std::cout << "\n========================================\n";
}

void addRouteUI(ClubManager& club) {
    std::cout << "\n========== ADD ROUTE ==========\n";

    std::string name = readText("Peak name: ");
    std::string mountain = readText("Mountain: ");
    int altitude = readInt("Altitude (m): ", 1, 9000);
    int difficulty = readInt("Difficulty (1-12): ", 1, 12);
    double duration = readDouble("Duration (hours): ", 0.1, 1000);
    std::string region = readText("Region: ");

    int equipmentCount = readInt("Number of equipment items: ", 0, 100);

    std::vector<std::string> equipment;

    for (int i = 0; i < equipmentCount; i++) {
        std::string item = readText(
            "Equipment " + std::to_string(i + 1) + ": "
        );

        equipment.push_back(item);
    }

    ClimbingRoute route(
        name,
        mountain,
        altitude,
        static_cast<Difficulty>(difficulty),
        duration,
        equipment,
        region
    );

    club.addRoute(route);
}

void addClimberUI(ClubManager& club) {
    std::cout << "\n========== ADD CLIMBER ==========\n";

    int id;

    while (true) {
        id = readInt("Climber ID: ", 1, 1000000);

        bool exists = false;

        for (const Climber& climber : club.getClimbers()) {
            if (climber.getClimberId() == id) {
                exists = true;
                break;
            }
        }

        if (exists) {
            std::cout << "Error: Climber ID already exists!\n";
            std::cout << "Please enter another ID.\n\n";
            continue;
        }

        break;
    }

    std::string name = readText("Full name: ");

    std::cout << "\nExperience levels:\n";
    std::cout << "1. Beginner\n";
    std::cout << "2. Intermediate\n";
    std::cout << "3. Advanced\n";
    std::cout << "4. Expert\n";

    int experience = readInt("Experience: ", 1, 4);
    int insuranceId = readInt("Insurance ID: ", 1, 2000000000);
    std::string startingDate = readDate("Starting date: (DD-MM-YYYY)");
    std::string endingDate = readDate("Ending date: (DD-MM-YYYY)");

    Climber climber(
        id,
        name,
        static_cast<Experience>(experience),
        insuranceId,
        {}
    );

    Insurance insurance(insuranceId,startingDate,endingDate);

    club.addClimber(climber);
    club.addInsurance(insurance);
}

void showRoutesUI(const ClubManager& club) {
    std::cout << "\n========== ALL ROUTES ==========\n";
    club.printRoutes();
}

void showClimbersUI(const ClubManager& club) {
    std::cout << "\n========== ALL CLIMBERS ==========\n";
    club.printClimbers();
}

void filterByMountainUI(const ClubManager& club) {
    std::string mountain = readText("Enter mountain: ");
    bool found = false;

    for (const ClimbingRoute& route : club.getRoutes()) {
        if (route.getMountain() == mountain) {
            club.printRoute(route);
            found = true;
        }
    }

    if (!found) {
        std::cout << "No routes found!\n";
    }
}

void filterByDifficultyUI(const ClubManager& club) {
    int difficulty = readInt("Difficulty (1-12): ", 1, 12);
    bool found = false;

    for (const ClimbingRoute& route : club.getRoutes()) {
        if (route.getDifficulty() == static_cast<Difficulty>(difficulty)) {
            club.printRoute(route);
            found = true;
        }
    }

    if (!found) {
        std::cout << "No routes found!\n";
    }
}

void registerClimbUI(ClubManager& club) {
    std::cout << "\n========== REGISTER CLIMB ==========\n";

    const std::vector<ClimbingRoute>& routes = club.getRoutes();
    const std::vector<Climber>& climbers = club.getClimbers();

    if (routes.empty() || climbers.empty()) {
        std::cout << "Routes or climbers are missing!\n";
        return;
    }

    std::cout << "\nAvailable routes:\n";

    for (size_t i = 0; i < routes.size(); i++) {
        std::cout << i + 1 << ". "
                  << routes[i].getName()
                  << " - UIAA "
                  << routes[i].getDifficulty() << "\n";
    }

    int routeChoice = readInt(
        "\nSelect route: ",
        1,
        static_cast<int>(routes.size())
    );

    std::cout << "\nAvailable climbers:\n";

    for (const Climber& climber : climbers) {
        std::cout << climber.getClimberId() << ". "
                  << climber.getFullName() << "\n";
    }

    const Climber* selectedClimber = nullptr;

    while (selectedClimber == nullptr) {
        int climberId = readInt(
            "\nEnter climber ID: ",
            1,
            1000000
        );

        for (const Climber& climber : climbers) {
            if (climber.getClimberId() == climberId) {
                selectedClimber = &climber;
                break;
            }
        }

        if (selectedClimber == nullptr) {
            std::cout << "Error: Climber not found!\n";
            std::cout << "Please try again.\n";
        }
    }

    const ClimbingRoute& selectedRoute = routes[routeChoice - 1];

    if (!club.checkExperience(
            selectedClimber->getExperience(),
            selectedRoute.getDifficulty())) {
        throw std::runtime_error("Insufficient experience!");
    }

    club.registerClimb(selectedRoute, *selectedClimber);
}

void showClimberInfoUI(ClubManager& club) {
    std::cout << "\n========== SHOW CLIMBER'S INFO ==========\n";
    int id = readInt("Enter id number: ", 1, 1000000);

    const Climber* climber = club.findClimberById(id);

    if (climber == nullptr) {
        std::cout << "Climber not found!\n";
        return;
    }

    club.showClimberInfo(*climber);
}

int main() {
    try {
        ClubManager club;
        club.loadData();

        int choice;

        do {
            printMenu();

            choice = readInt("Enter your choice: ", 0, 7);

            try {
                switch (choice) {
                    case 1:
                        addRouteUI(club);
                        break;

                    case 2:
                        addClimberUI(club);
                        break;

                    case 3:
                        registerClimbUI(club);
                        break;

                    case 4:
                        showRoutesUI(club);
                        break;

                    case 5:
                        showClimbersUI(club);
                        break;

                    case 6:
                        showClimberInfoUI(club);
                        break;

                    case 7:
                        filterByDifficultyUI(club);
                        break;

                    case 8:
                        filterByMountainUI(club);
                        break;

                    case 0:
                        std::cout << "Goodbye!\n";
                        break;
                }

            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } while (choice != 0);

    } catch (const std::exception& e) {
        std::cerr << "Application error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
