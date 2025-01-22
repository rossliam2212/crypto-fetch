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
        ("set-apikey", "Set coinmarketcap api key", cxxopts::value<std::string>())
        ("get-apikey", "Get location of coinmarketcap api key if set");
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

std::string CommandLineParser::getSuppliedApiKey() const {
    return result[CMD_API_KEY_SET].as<std::string>();
}

void CommandLineParser::handleVersion() {
    fmt::println("{} version {}", project_name, project_version);
    std::exit(EXIT_SUCCESS);
}

void CommandLineParser::handleGetApiKey() {
    if (checkApiKeyFile()) {
        fmt::println("[INFO] API key located in file - '{}'", getFullApiKeyFilePath());
        std::exit(EXIT_SUCCESS);
    }
    fmt::println("[WARN] API key not set. See: --set-apikey");
    std::exit(EXIT_SUCCESS);
}

void CommandLineParser::handleSetApiKey() {
    const std::string apiKeyFilePath = getFullApiKeyFilePath();
    if (checkApiKeyFile()) {
        fmt::println("[INFO] API key already set in file - '{}'", apiKeyFilePath);
        std::exit(EXIT_SUCCESS);
    }

    if (rootDirExists()) {
        writeApiKeyToFile(apiKeyFilePath, getSuppliedApiKey());
        std::exit(EXIT_SUCCESS);
    }
    createRootDir();
    writeApiKeyToFile(apiKeyFilePath, getSuppliedApiKey());
    std::exit(EXIT_SUCCESS);
}

bool CommandLineParser::checkApiKeyFile() {
    const std::string fallbackFilePath = getFullApiKeyFilePath();
    return fileExists(fallbackFilePath);
}

bool CommandLineParser::rootDirExists() {
    const std::string rootDir = fmt::format("{}{}", getenv("HOME"), API_KEY_ROOT);
    return fs::exists(rootDir) && fs::is_directory(rootDir);
}

bool CommandLineParser::fileExists(const std::string_view path) {
    return fs::exists(path);
}

void CommandLineParser::createRootDir() {
    const std::string rootDir = fmt::format("{}{}", getenv("HOME"), API_KEY_ROOT);
    fs::create_directories(rootDir);
}

void CommandLineParser::writeApiKeyToFile(const std::string& path, const std::string& apiKey) {
    std::ofstream out{path, std::fstream::out};
    if (out.is_open()) {
        out << apiKey << std::endl;
        fmt::println("[INFO] API key successfully written to - '{}'", path);
    }
    out.close();
}

std::string CommandLineParser::getFullApiKeyFilePath() {
    return fmt::format("{}{}{}", getenv("HOME"), API_KEY_ROOT, API_KEY);
}
