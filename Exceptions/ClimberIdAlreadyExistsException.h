#ifndef UNTITLED1_CLIMBERIDALREADYEXISTSEXCEPTION_H
#define UNTITLED1_CLIMBERIDALREADYEXISTSEXCEPTION_H
#include <stdexcept>

class ClimberIdAlreadyExistsException :public std::runtime_error {
  public:
  ClimberIdAlreadyExistsException():std::runtime_error("Climber Id already exists") {};
};

#endif //UNTITLED1_CLIMBERIDALREADYEXISTSEXCEPTION_H
