#include "Insurance.h"
#include <stdexcept>

Insurance::Insurance(int insuranceId,
                     std::string startDate,
                     std::string expiryDate)
    : insuranceId(insuranceId),
      startDate(startDate),
      expiryDate(expiryDate) {

    if (insuranceId <= 0) {
        throw std::invalid_argument("Invalid insurance ID!");
    }

    if (startDate > expiryDate) {
        throw std::invalid_argument("Invalid insurance dates!");
    }
}

int Insurance::getInsuranceId() const {
    return insuranceId;
}

std::string Insurance::getStartDate() const {
    return startDate;
}

std::string Insurance::getExpiryDate() const {
    return expiryDate;
}

bool Insurance::isValid(const std::string& climbingDate) const {
    auto reverseDate = [](const std::string& date) {
        return date.substr(6, 4) + "-" +
               date.substr(3, 2) + "-" +
               date.substr(0, 2);
    };

    return reverseDate(climbingDate) >= reverseDate(startDate) &&
           reverseDate(climbingDate) <= reverseDate(expiryDate);
}