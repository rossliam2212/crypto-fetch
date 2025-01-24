/**
 * @file CommandLineParser.cpp
 * @author liam 
 * @date 07/01/2025
 */

#include "cf/CommandLineParser.hpp"

namespace cf {
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
        } catch (const ApiKeyException& ex) {
            throw CryptoFetchException(fmt::format("API Key error - {}", ex.what()));
        } catch (const std::exception& ex) {
            throw CryptoFetchException(fmt::format("CMD parsing error - {}", ex.what()));
        }
    }

    std::vector<std::string> CommandLineParser::getTickers() const {
        auto tickers = result[CMD_TICKER].as<std::vector<std::string>>();
        for (auto& ticker : tickers) {
            std::transform(std::begin(ticker), std::end(ticker), std::begin(ticker),
                [](const char c) { return toupper(c); });
        }
        return tickers;
    }

    std::string CommandLineParser::getCurrency() const {
        auto currency = result[CMD_CURRENCY].as<std::string>();
        std::transform(std::begin(currency), std::end(currency), std::begin(currency),
            [](const char c) { return toupper(c); });

        return currency;
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
        const std::string apiKeyPath = getFullApiKeyFilePath();

        if (utils::fileExists(apiKeyPath)) {
            fmt::println("[INFO] API key located in config file - '{}'", getFullApiKeyFilePath());
            std::exit(EXIT_SUCCESS);
        }
        fmt::println("[WARN] API key not set. See: --set-apikey");
        std::exit(EXIT_SUCCESS);
    }

    void CommandLineParser::handleSetApiKey() const {
        const std::string apiKeyFilePath = getFullApiKeyFilePath();

        if (utils::fileExists(apiKeyFilePath)) {
            fmt::println("[INFO] API key already set in config file - '{}'", apiKeyFilePath);
            std::exit(EXIT_SUCCESS);
        }

        const std::string rootDirectory = getRootDirectoryPath();
        const std::string suppliedApiKey = getSuppliedApiKey();
        if (utils::directoryExists(rootDirectory)) {
            writeApiKeyToFile(apiKeyFilePath, suppliedApiKey);
            std::exit(EXIT_SUCCESS);
        }

        if (utils::createDirectory(rootDirectory)) {
            writeApiKeyToFile(apiKeyFilePath, suppliedApiKey);
            std::exit(EXIT_SUCCESS);
        }
        throw ApiKeyException(fmt::format("Failed to create api key root directory - '{}'", rootDirectory));
    }

    void CommandLineParser::writeApiKeyToFile(const std::string& path, const std::string& apiKey) {
        std::ofstream out{path, std::fstream::out};
        if (out.is_open()) {
            out << apiKey << std::endl;
            fmt::println("[INFO] API key successfully written to - '{}'", path);
            out.close();
        } else {
            throw ApiKeyException("Failed to write API key to config file");
        }
    }

    std::string CommandLineParser::getRootDirectoryPath() {
        return fmt::format("{}{}", getenv(HOME_ENV_VAR), API_KEY_ROOT);;
    }

    std::string CommandLineParser::getFullApiKeyFilePath() {
        return fmt::format("{}{}{}", getenv("HOME"), API_KEY_ROOT, API_KEY);
    }
} // namespace cf