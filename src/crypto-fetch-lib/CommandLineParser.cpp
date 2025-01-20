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
        ("help", "Print usage information")
        ("set-apikey", "Set coinmarketcap api key file path", cxxopts::value<std::string>())
        ("get-apikey", "Get coinmarketcap api key file path if set");
}

void CommandLineParser::parse(int argc, char** argv) {
    try {
        result = options.parse(argc, argv);

        if (result.count(CMD_HELP)) {
            fmt::println(options.help());
            std::exit(EXIT_SUCCESS);
        }

        if (result.count(CMD_VERSION)) {
            handleVersion();
        }

        if (result.count(CMD_API_KEY_GET)) {
            handleGetApiKey();
        }

        if (result.count(CMD_API_KEY_SET)) {
            handleSetApiKey();
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

std::string CommandLineParser::getApiKeyPath() const {
    return result[CMD_API_KEY_SET].as<std::string>();
}

void CommandLineParser::handleVersion() {
    fmt::println("{} version {}", project_name, project_version);
    std::exit(EXIT_SUCCESS);
}

void CommandLineParser::handleGetApiKey() {
    if (const char* path = std::getenv(API_KEY_ENVIRONMENT_VAR)) {
        spdlog::info("API key path: '{}'", path);
    } else {
        spdlog::warn("API key path not set. See: --set-apikey");
    }
    std::exit(EXIT_SUCCESS);
}


void CommandLineParser::handleSetApiKey() {
    const std::string suppliedPath = getApiKeyPath();

    if (const char* path = std::getenv(API_KEY_ENVIRONMENT_VAR)) {
        if (path == suppliedPath) {
            fmt::println("API key path already set. Path: '{}'", path);
        } else {
            if (setApiKeyEnvVar(suppliedPath)) {
                spdlog::info("New API key path written to ~/.bashrc. New path: '{}'", suppliedPath);
            } else {
                spdlog::error("Failed to write API key path to ~/.bashrc");
                std::exit(EXIT_FAILURE);
            }
        }
    } else {
        if (setApiKeyEnvVar(suppliedPath)) {
            spdlog::info("API key path written to ~/.bashrc. New path: '{}'", suppliedPath);
        } else {
            spdlog::error("Failed to write API key path to ~/.bashrc");
            std::exit(EXIT_FAILURE);
        }
    }
    std::exit(EXIT_SUCCESS);
}

bool CommandLineParser::setApiKeyEnvVar(const std::string& suppliedPath) {
    std::ofstream bashrc;
    bashrc.open(std::getenv("HOME") + std::string("/.bashrc"), std::ios::app);

    if (bashrc.is_open()) {
        bashrc << "export " << API_KEY_ENVIRONMENT_VAR << "=" << suppliedPath << std::endl;
        bashrc.close();
        return true;
    }
    return false;
}
