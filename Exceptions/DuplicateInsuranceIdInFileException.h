#ifndef UNTITLED1_DUPLICATEINSURANCEIDINFILEEXCEPTION_H
#define UNTITLED1_DUPLICATEINSURANCEIDINFILEEXCEPTION_H
#include <stdexcept>

class DuplicateInsuranceIdInFileException:public std::runtime_error {
    public:
    DuplicateInsuranceIdInFileException():std::runtime_error
        ("Duplicate Insurance Id In file! ") {};
};

#endif //UNTITLED1_DUPLICATEINSURANCEIDINFILEEXCEPTION_H
