/**
 * @file ApiResponse.cpp
 * @author liam 
 * @date 14/01/2025
 */

#include "cf/ApiResponse.hpp"

namespace cf {
    ApiResponse::ApiResponse(const CommandLineParser& parser, nlohmann::json& data)
        : verbose{parser.isVerbose()} {
        parse(parser, data);
    }

    std::vector<ResponseData> ApiResponse::getResponses() const {
        return responses;
    }

    bool ApiResponse::isVerbose() const {
        return verbose;
    }

    void ApiResponse::parse(const CommandLineParser& parser, nlohmann::json& data) {
        const auto tickers = parser.getTickers();
        const std::string currency = parser.getCurrency();

        try {
            for (const auto& ticker : tickers) {
                ResponseData responseData;
                responseData.ticker = ticker;
                responseData.currency = currency;

                responseData.price = parseValue("price", data, ticker, currency);

                if (verbose) {
                    responseData.marketCap = parseValue("market_cap", data, ticker, currency);
                    responseData.volume24hr = parseValue("volume_24h", data, ticker, currency);
                    responseData.percentChange1hr = parseValue("percent_change_1h", data, ticker, currency);
                    responseData.percentChange24hr = parseValue("percent_change_24h", data, ticker, currency);
                }
                responses.emplace_back(responseData);
            }
        } catch (const std::exception& ex) {
            throw CryptoFetchException(fmt::format("Response parse error - {}", ex.what()));
        }
    }

    std::string ApiResponse::parseValue(std::string_view value,
                                        nlohmann::json& data,
                                        std::string_view ticker,
                                        std::string_view currency) {
        const double valueAsDouble = data["data"][ticker]["quote"][currency][value].get<double>();
        return fmt::to_string(valueAsDouble);
    }
} // namespace cf
