#ifndef UNTITLED1_INSURANCE_H
#define UNTITLED1_INSURANCE_H

#endif //UNTITLED1_INSURANCE_H

#pragma once

#include <string>

class Insurance {
    int insuranceId;
    std::string startDate;
    std::string expiryDate;

public:
    Insurance() = default;

    Insurance(int insuranceId,
              std::string startDate,
              std::string expiryDate);

    int getInsuranceId() const;
    std::string getStartDate() const;
    std::string getExpiryDate() const;

    bool isValid(const std::string& climbingDate) const;
};
