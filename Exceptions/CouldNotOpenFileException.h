#ifndef UNTITLED1_COULDNOTOPENFILEEXCEPTION_H
#define UNTITLED1_COULDNOTOPENFILEEXCEPTION_H
#include <stdexcept>
#include <string>

class CouldNotOpenFileException: public std::runtime_error {
  public:
  CouldNotOpenFileException(std::string message):
    std::runtime_error("Could not open file: "  + message) {};
};

#endif //UNTITLED1_COULDNOTOPENFILEEXCEPTION_H
