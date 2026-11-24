#ifndef UNTITLED1_INSUFFICIENTEXPERIENCEEXCEPTION_H
#define UNTITLED1_INSUFFICIENTEXPERIENCEEXCEPTION_H
#include <exception>
#include <stdexcept>

class InsufficientExperienceException : public std::runtime_error {
    public:
    InsufficientExperienceException(): std::runtime_error("Insufficient Experience Exception") {};
} ;

#endif //UNTITLED1_INSUFFICIENTEXPERIENCEEXCEPTION_H
