#ifndef UNTITLED1_INPUTEXCEPTIONS_H
#define UNTITLED1_INPUTEXCEPTIONS_H

#pragma once
#include <stdexcept>

class EmptyFieldException : public std::runtime_error {
public:
    EmptyFieldException()
        : std::runtime_error("Field cannot be empty!") {}
};

class InvalidCharacterException : public std::runtime_error {
public:
    InvalidCharacterException()
        : std::runtime_error("Invalid character!") {}
};

class InvalidDateFormatException : public std::runtime_error {
    public:
    InvalidDateFormatException():std::runtime_error("Invalid date format!") {}
};

class InvalidCalendarDateException:public std::runtime_error {
  public:
    InvalidCalendarDateException():std::runtime_error("Invalid calendar date!") {}
};

class InvalidNumberException:public std::runtime_error {
    public:
    InvalidNumberException():std::runtime_error("Invalid number!") {}
};

class ValueOutOfRangeException:public std::runtime_error {
  public:
    ValueOutOfRangeException():std::runtime_error("Value out of range!") {}
};

#endif //UNTITLED1_INPUTEXCEPTIONS_H