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
#include <algorithm>

#include "config.hpp"
#include "Defines.hpp"
#include "FileUtils.hpp"
#include "exceptions/CryptoFetchException.hpp"
#include "exceptions/ApiKeyException.hpp"

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
        void handleSetApiKey() const;

        static void handleVersion();
        static void handleGetApiKey();
        static void writeApiKeyToFile(const std::string& path, const std::string& apiKey);
        static std::string getRootDirectoryPath();
        static std::string getFullApiKeyFilePath();
    };
} // namespace cf
#endif //COMMANDLINEPARSER_HPP
