#ifndef UNTITLED1_INSURANCENOTFOUNDEXCEPTION_H
#define UNTITLED1_INSURANCENOTFOUNDEXCEPTION_H
#include <stdexcept>

class InsuranceNotFoundException:public std::runtime_error {
    public:
    InsuranceNotFoundException():std::runtime_error("Insurance not found!") {};
};

#endif //UNTITLED1_INSURANCENOTFOUNDEXCEPTION_H
