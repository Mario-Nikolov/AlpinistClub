#include "FileUtils.h"
#include "InvalidFileDataException.h"

std::string readField(std::stringstream& ss, char separator) {
    std::string value;

    if (!std::getline(ss, value, separator)) {
        throw InvalidFileDataException();
    }

    return value;
}