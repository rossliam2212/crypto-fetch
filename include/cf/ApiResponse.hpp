/**
 * @file ApiResponse.hpp
 * @author liam 
 * @date 14/01/2025
 */

#ifndef APIRESPONSE_HPP
#define APIRESPONSE_HPP

#include <nlohmann/json.hpp>

#include "CommandLineParser.hpp"

namespace cf {
    struct ResponseData {
        std::string ticker;
        std::string currency;
        std::string price;
        std::string marketCap{"null"};
        std::string volume24hr{"null"};
        std::string percentChange1hr{"null"};
        std::string percentChange24hr{"null"};
    };

    class ApiResponse {
    public:
        ApiResponse(const CommandLineParser& parser, nlohmann::json& data);
        ~ApiResponse() = default;

        std::vector<ResponseData> getResponses() const;
        bool isVerbose() const;

    private:
        std::vector<ResponseData> responses;
        bool verbose;

        void parse(const CommandLineParser& parser, nlohmann::json& data);

        static std::string parseValue(std::string_view value, nlohmann::json& data, std::string_view ticker, std::string_view currency);
    };
} // namespace cf

#endif //APIRESPONSE_HPP
