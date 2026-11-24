#ifndef UNTITLED1_COULDNOTSAVECLIMBEREXCEPTION_H
#define UNTITLED1_COULDNOTSAVECLIMBEREXCEPTION_H
#include <stdexcept>

class CouldNotSaveClimberException :public std::runtime_error {
    public:
    CouldNotSaveClimberException():std::runtime_error("Could not save climber! ") {};
};
#endif //UNTITLED1_COULDNOTSAVECLIMBEREXCEPTION_H
