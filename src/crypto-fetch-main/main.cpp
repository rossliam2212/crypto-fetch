#include "ApiClient.hpp"
#include "Formatter.hpp"

std::string getApiKeyPath() {
    if (const char* path = std::getenv(API_KEY_ENVIRONMENT_VAR)) {
        return fmt::to_string(path);
    }
    throw std::runtime_error("API key not set. See: --set-apikey");
}

std::string loadApiKey() {
    const std::string path = getApiKeyPath();
    std::ifstream ifs(path, std::ios::in);

    if (!ifs.is_open()) {
        throw std::runtime_error(fmt::format("Failed to open api key file '{}'", path));
    }
    std::string apiKey;
    std::getline(ifs, apiKey);

    if (apiKey.empty()) {
        throw std::runtime_error(fmt::format("Failed to read api key from file '{}'", path));
    }
    ifs.close();
    return apiKey;
}

int main(int argc, char** argv) {
    try {
        CommandLineParser parser;
        parser.parse(argc, argv);

        const std::string apiKey = loadApiKey();
        const ApiClient client{apiKey};

        const auto response = client.fetchLatestPrice(parser);
        Formatter::display(response);
    } catch (const std::exception& ex) {
        spdlog::error("Failed to fetch price. Cause: '{}'.", ex.what());
    }
}