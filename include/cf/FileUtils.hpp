/**
 * @file FileUtils.hpp
 * @author liam 
 * @date 24/01/2025
 */

#ifndef FILEUTILS_HPP
#define FILEUTILS_HPP

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace cf::utils {
    bool fileExists(const std::string_view filePath);
    bool directoryExists(const std::string_view dirPath);
    bool createDirectory(const std::string_view dirPath);
} // namespace cf::utils

#endif //FILEUTILS_HPP
