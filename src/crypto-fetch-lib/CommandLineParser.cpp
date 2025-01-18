/**
 * @file CommandLineParser.cpp
 * @author liam 
 * @date 07/01/2025
 */

#include "CommandLineParser.hpp"

CommandLineParser::CommandLineParser()
    : options{"crypto-price", "A tool to fetch cryptocurrency prices (API: coinmarketcap)"} {
    options.add_options()
        ("t,ticker", "Cryptocurrency ticker symbol(s)", cxxopts::value<std::vector<std::string>>())
        ("c,currency", "Fiat currency", cxxopts::value<std::string>()->default_value(DEFAULT_CURRENCY))
        ("v,verbose", "Print verbose output", cxxopts::value<bool>()->default_value("false"))
        ("version", "Print version information")
        ("help", "Print usage information");
}

void CommandLineParser::parse(int argc, char** argv) {
    try {
        result = options.parse(argc, argv);

        if (result.count(CMD_HELP)) {
            fmt::println(options.help());
            std::exit(EXIT_SUCCESS);
        }

        if (result.count(CMD_VERSION)) {
            fmt::println("{} version {}", project_name, project_version);
            std::exit(EXIT_SUCCESS);
        }

        if (!result.count(CMD_TICKER)) {
            throw std::runtime_error("Ticker option not specified");
        }
    } catch (const std::exception& ex) {
        throw std::runtime_error(fmt::format("CMD parsing error - {}", ex.what()));
    }
}

std::vector<std::string> CommandLineParser::getTickers() const {
    return result[CMD_TICKER].as<std::vector<std::string>>();
}

std::string CommandLineParser::getCurrency() const {
    return result[CMD_CURRENCY].as<std::string>();
}

bool CommandLineParser::isVerbose() const {
    return result.count(CMD_VERBOSE);
}
