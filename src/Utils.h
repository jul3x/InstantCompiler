#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <string>

inline bool parseFilename(const std::string &filename) {
    if (filename.empty())
        return false;

    if (filename.find_first_not_of("0123456789") == std::string::npos)
        return false;

    if (filename.find_first_of(".-=+`~!@#$%^&*()[{]}\\|\'\";:<,>./?") != std::string::npos)
        return false;

    return true;
}

#endif