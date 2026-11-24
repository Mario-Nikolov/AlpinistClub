#ifndef UNTITLED1_INVALIDWEATHEREXCEPTION_H
#define UNTITLED1_INVALIDWEATHEREXCEPTION_H
#include <stdexcept>

class InvalidWeatherException : public std::runtime_error {
    public:
    InvalidWeatherException():std::runtime_error("Invalid Weather!") {}
};

#endif //UNTITLED1_INVALIDWEATHEREXCEPTION_H