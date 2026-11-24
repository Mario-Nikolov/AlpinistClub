#ifndef UNTITLED1_INSURANCEALREADYEXISTSEXCEPTION_H
#define UNTITLED1_INSURANCEALREADYEXISTSEXCEPTION_H
#include <stdexcept>

class InsuranceAlreadyExistsException :public std::runtime_error {
    public:
    InsuranceAlreadyExistsException():std::runtime_error("Insurance already exists! ") {};
};
#endif //UNTITLED1_INSURANCEALREADYEXISTSEXCEPTION_H
