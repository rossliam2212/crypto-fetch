/**
 * @file CommandLineParser.hpp
 * @author liam 
 * @date 07/01/2025
 */

#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include <cxxopts.hpp>
#include <fmt/core.h>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "config.hpp"
#include "Defines.hpp"

namespace fs = std::filesystem;

namespace cf {
    class CommandLineParser {
    public:
        CommandLineParser();
        ~CommandLineParser() = default;

        void parse(int argc, char** argv);
        std::vector<std::string> getTickers() const;
        std::string getCurrency() const;
        bool isVerbose() const;

    private:
        cxxopts::Options options;
        cxxopts::ParseResult result;

        std::string getSuppliedApiKey() const;
        void handleSetApiKey();

        static void handleVersion();
        static void handleGetApiKey();
        static bool checkApiKeyFile();
        static bool fileExists(std::string_view path);
        static bool rootDirExists();
        static void createRootDir();
        static void writeApiKeyToFile(const std::string& path, const std::string& apiKey);
        static std::string getFullApiKeyFilePath();
    };
} // namespace cf
#endif //COMMANDLINEPARSER_HPP
