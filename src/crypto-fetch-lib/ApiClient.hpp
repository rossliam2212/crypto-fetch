/**
 * @file ApiClient.hpp
 * @author liam 
 * @date 07/01/2025
 */

#ifndef APICLIENT_HPP
#define APICLIENT_HPP

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include <fmt/ranges.h>
#include <list>

#include "ApiResponse.hpp"

class ApiClient {
public:
    ApiClient(const std::string& apiKey);
    ~ApiClient() = default;

    ApiResponse fetchLatestPrice(const CommandLineParser& parser) const;

private:
    std::string apiKey;

    static void displayFetchingMessage(const std::vector<std::string>& tickers);
    static std::string constructURL(const std::vector<std::string>& tickers, std::string_view currency);
};

#endif //APICLIENT_HPP
