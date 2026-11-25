cmake_minimum_required(VERSION 4.3)
project(AlpinistClub)

set(CMAKE_CXX_STANDARD 20)

add_executable(AlpinistClub main.cpp
        Entity/enums.h
        Entity/ClimbingRoute.h
        Entity/ClimbingRoute.cpp
        Entity/Climber.h
        Entity/Climber.cpp
        Entity/Group.h
        Entity/Group.cpp
        Entity/AscentLog.cpp
        Entity/AscentLog.h
        ClubManager.h
        ClubManager.cpp
        Entity/Insurance.h
        Entity/Insurance.cpp
        Exceptions/InvalidInsuranceException.h
        Exceptions/InputExceptions.h
        Exceptions/InvalidFileDataException.h
        Exceptions/InvalidWeatherException.h
        Exceptions/InvalidDifficultyException.h
        Exceptions/GroupExceptions.h
        Exceptions/CouldNotOpenFileException.h
        Exceptions/CouldNotSaveRouteException.h
        Exceptions/ClimberIdAlreadyExistsException.h
        Exceptions/InvalidAscentException.h
        Exceptions/CouldNotSaveClimberException.h
        Exceptions/InsuranceAlreadyExistsException.h
        Exceptions/CouldNotSaveInsuranceException.h
        Exceptions/InvalidExperienceException.h
        Exceptions/InvalidInsuranceDataException.h
        Exceptions/DuplicateInsuranceIdInFileException.h
        Exceptions/InsufficientExperienceException.h
        Exceptions/InsuranceNotFoundException.h
        Repository/ClimberRepository.h
        Repository/ClimberRepository.cpp
        Utils/FileUtils.h
        Utils/FileUtils.cpp)

target_include_directories(AlpinistClub PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Entity
        ${CMAKE_CURRENT_SOURCE_DIR}/Repository
        ${CMAKE_CURRENT_SOURCE_DIR}/Exceptions
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
)