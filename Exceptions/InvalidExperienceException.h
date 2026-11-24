#ifndef UNTITLED1_INVALIDEXPERIENCEEXCEPTION_H
#define UNTITLED1_INVALIDEXPERIENCEEXCEPTION_H
#include <stdexcept>

class InvalidExperienceException :public std::runtime_error {
    public:
    InvalidExperienceException():std::runtime_error("Invalid experience! ") {};
};

#endif //UNTITLED1_INVALIDEXPERIENCEEXCEPTION_H
