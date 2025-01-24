/**
 * @file FileUtils.cpp
 * @author liam 
 * @date 24/01/2025
 */

#include "cf/FileUtils.hpp"

namespace cf::utils {
    bool fileExists(const std::string_view filePath) {
        return fs::exists(filePath);
    }
    bool directoryExists(const std::string_view dirPath) {
        return fs::exists(dirPath) && fs::is_directory(dirPath);
    }

    bool createDirectory(const std::string_view dirPath) {
        return fs::create_directories(dirPath);
    }
} // namespace cf::utils