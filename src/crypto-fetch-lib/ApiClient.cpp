/**
 * @file ApiClient.cpp
 * @author liam 
 * @date 07/01/2025
 */

#include "cf/ApiClient.hpp"

namespace cf {
    ApiClient::ApiClient(const std::string& apiKey)
        : apiKey{apiKey} {
    }

    ApiResponse ApiClient::fetchLatestPrice(const CommandLineParser& parser) const {
        displayFetchingMessage(parser.getTickers());

        try {
            curlpp::Cleanup cleanup;

            const std::string url = constructURL(parser.getTickers(), parser.getCurrency());
            const std::list<std::string> headers = {
                HEADER_API_KEY + (": " + apiKey),
                HEADER_ACCEPT
            };

            std::ostringstream response;
            curlpp::Easy request;
            request.setOpt<curlpp::options::Url>(url);
            request.setOpt<curlpp::options::HttpHeader>(headers);
            request.setOpt<curlpp::options::WriteStream>(&response);

            request.perform();
            auto data = nlohmann::json::parse(response.str());

            return ApiResponse{parser, data};
        } catch (const std::exception& ex) {
            throw std::runtime_error(fmt::format("Fetching error - {}", ex.what()));
        }
    }

    void ApiClient::displayFetchingMessage(const std::vector<std::string>& tickers) {
        const std::string tickerOutput = tickers.size() == 1 ?
            tickers.at(0) : fmt::to_string(fmt::join(tickers, ",$"));
        fmt::println("FETCHING PRICE DATA FOR TICKER(S): ${}\n", tickerOutput);
    }

    std::string ApiClient::constructURL(const std::vector<std::string>& tickers, const std::string_view currency) {
        const std::string tickersJoined = fmt::to_string(fmt::join(tickers, ","));
        return fmt::format("{}{}{}{}{}{}",
            API_BASE_URL, API_LATEST_ENDPOINT, API_SYMBOL_ARG, tickersJoined, API_CONVERT_ARG, currency);
    }
} // namespace cf