#ifndef UNTITLED1_COULDNOTSAVEINSURANCEEXCEPTION_H
#define UNTITLED1_COULDNOTSAVEINSURANCEEXCEPTION_H
#include <stdexcept>

class CouldNotSaveInsuranceException :public std::runtime_error {
    public:
    CouldNotSaveInsuranceException():std::runtime_error("Could not save insurance! ") {};
};

#endif //UNTITLED1_COULDNOTSAVEINSURANCEEXCEPTION_H
