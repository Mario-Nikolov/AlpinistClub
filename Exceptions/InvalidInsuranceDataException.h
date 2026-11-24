#ifndef UNTITLED1_INVALIDINSURANCEDATAEXCEPTION_H
#define UNTITLED1_INVALIDINSURANCEDATAEXCEPTION_H
#include <stdexcept>

class InvalidInsuranceDataException :public std::runtime_error {
    public:
    InvalidInsuranceDataException():std::runtime_error("Invalid Insurance data! ") {};
};

#endif //UNTITLED1_INVALIDINSURANCEDATAEXCEPTION_H
