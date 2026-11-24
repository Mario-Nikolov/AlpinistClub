#ifndef UNTITLED1_INVALIDFILEDATAEXCEPTION_H
#define UNTITLED1_INVALIDFILEDATAEXCEPTION_H
#include <stdexcept>

class InvalidFileDataException:public std::runtime_error {
    public:
    InvalidFileDataException():std::runtime_error("Invalid File data! ") {}
};

#endif //UNTITLED1_INVALIDFILEDATAEXCEPTION_H
