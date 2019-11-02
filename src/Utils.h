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

inline std::tuple<std::string, std::string, std::string> generateOutNames(const std::string &in_file, const std::string &ext) {
    auto slash_iter = in_file.find_last_of('/');
    auto dot_iter = in_file.find_last_of('.');

    std::string directory = slash_iter == std::string::npos ? "." : in_file.substr(0, slash_iter);
    std::string class_name = in_file.substr(slash_iter + 1,
        (dot_iter == std::string::npos ? in_file.length() : dot_iter) - slash_iter - 1);
    std::string out_file = directory + "/" + class_name + "." + ext;

    return std::make_tuple(directory, class_name, out_file);
}

#endif