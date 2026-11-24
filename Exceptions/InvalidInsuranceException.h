#ifndef UNTITLED1_INVALIDINSURANCEEXCEPTION_H
#define UNTITLED1_INVALIDINSURANCEEXCEPTION_H
#include <stdexcept>
#include <string>

class InvalidInsuranceException : public std::runtime_error {
    public:
        explicit InvalidInsuranceException() : runtime_error("Invalid Insurance") {};
};

#endif //UNTITLED1_INVALIDINSURANCEEXCEPTION_H
