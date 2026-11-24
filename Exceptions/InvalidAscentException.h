#ifndef UNTITLED1_INVALIDASCENTEXCEPTION_H
#define UNTITLED1_INVALIDASCENTEXCEPTION_H
#include <stdexcept>

class InvalidAscentException :public std::runtime_error {
    public:
    InvalidAscentException():std::runtime_error("Invalid ascent! ") {};
};
#endif //UNTITLED1_INVALIDASCENTEXCEPTION_H
