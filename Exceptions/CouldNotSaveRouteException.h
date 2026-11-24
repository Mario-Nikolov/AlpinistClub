#ifndef UNTITLED1_COULDNOTSAVEROUTEEXCEPTION_H
#define UNTITLED1_COULDNOTSAVEROUTEEXCEPTION_H
#include <stdexcept>

class CouldNotSaveRouteException : public std::runtime_error {
    public:
    CouldNotSaveRouteException():std::runtime_error("Could not save route! ") {};
};
#endif //UNTITLED1_COULDNOTSAVEROUTEEXCEPTION_H
