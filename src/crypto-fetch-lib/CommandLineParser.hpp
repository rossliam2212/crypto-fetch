/**
 * @file CommandLineParser.hpp
 * @author liam 
 * @date 07/01/2025
 */

#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include <cxxopts.hpp>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "config.hpp"
#include "Defines.hpp"

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
};

#endif //COMMANDLINEPARSER_HPP
