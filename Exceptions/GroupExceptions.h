#ifndef UNTITLED1_GROUPEXCEPTIONS_H
#define UNTITLED1_GROUPEXCEPTIONS_H
#include <stdexcept>

#endif //UNTITLED1_GROUPEXCEPTIONS_H

class InvalidLeaderExperienceException:public std::runtime_error {
    public:
    InvalidLeaderExperienceException():std::runtime_error("Invalid leader experience") {};
};

class InvalidGroupSizeException:public std::runtime_error {
    public:
    InvalidGroupSizeException():std::runtime_error("Invalid group size") {};
};

class InvalidMemberExperienceException:public std::runtime_error {
    public:
    InvalidMemberExperienceException():std::runtime_error("Invalid member") {};
};




