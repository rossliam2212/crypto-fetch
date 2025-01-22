#include "ApiClient.hpp"
#include "Formatter.hpp"

std::string loadApiKey() {
    const auto apiKeyFilePath = std::string{getenv(HOME_ENV_VAR) + API_KEY_ROOT + API_KEY};
    std::ifstream ifs{apiKeyFilePath, std::fstream::in};
    if (!ifs.is_open()) {
        throw std::runtime_error(fmt::format("Config file does not exist. See --set-apikey"));
    }
    std::string apiKey;
    std::getline(ifs, apiKey);
    if (apiKey.empty()) {
       throw std::runtime_error(fmt::format("Failed to read api key from file - {}", apiKeyFilePath));
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
        fmt::println("[ERROR] Failed to fetch price. Cause: '{}'.", ex.what());
    }
}