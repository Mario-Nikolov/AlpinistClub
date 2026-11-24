#ifndef UNTITLED1_INVALIDDIFFICULTYEXCEPTION_H
#define UNTITLED1_INVALIDDIFFICULTYEXCEPTION_H
#include <stdexcept>

class InvalidDifficultyException:public std::runtime_error {
  public:
  InvalidDifficultyException():std::runtime_error("Invalid Difficulty! ") {}
};

#endif //UNTITLED1_INVALIDDIFFICULTYEXCEPTION_H
