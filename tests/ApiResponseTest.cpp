/**
 * @file ApiResponseTest.cpp
 * @author liam
 * @date 18/01/2025
 */

#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <vector>

#include "ApiResponse.hpp"

TEST_CASE("apiResponse_constructedFromJson_singleCrypto_defaultCurrency", "[unit][api-response][json-parsing][single-crypto]") {
    auto mockResponse = R"({
        "data": {
            "XRP": {
                "quote": {
                    "EUR": {
                        "price": 2.5543
                    }
                }
            }
        }
    })"_json;

    CommandLineParser mockParser;
    char arg1[] = "crypto-fetch";
    char arg2[] = "-t";
    char arg3[] = "XRP";
    char* mockArgs[] = {arg1, arg2, arg3};
    mockParser.parse(3, mockArgs);

    ApiResponse response{mockParser, mockResponse};
    const std::vector<ResponseData> responseData = response.getResponses();
    REQUIRE(responseData.size() == 1);

    ResponseData dataObject = responseData.at(0);
    REQUIRE(dataObject.ticker == "XRP");
    REQUIRE(dataObject.price == "2.5543");
    REQUIRE(dataObject.currency == "EUR");
}

TEST_CASE("apiResponse_constructedFromJson_multipleCryptos_defaultCurrency", "[unit][api-response][json-parsing][multiple-cryptos]") {
    auto mockResponse = R"({
        "data": {
            "XRP": {
                "quote": {
                    "EUR": {
                        "price": 2.5543
                    }
                }
            },
            "BTC": {
                "quote": {
                    "EUR": {
                        "price": 101994.6643
                    }
                }
            }
        }
    })"_json;

    CommandLineParser mockParser;
    char arg1[] = "crypto-fetch";
    char arg2[] = "-t";
    char arg3[] = "XRP,BTC";
    char* mockArgs[] = {arg1, arg2, arg3};
    mockParser.parse(3, mockArgs);

    ApiResponse response{mockParser, mockResponse};
    const std::vector<ResponseData> responseData = response.getResponses();
    REQUIRE(responseData.size() == 2);

    REQUIRE(responseData.at(0).ticker == "XRP");
    REQUIRE(responseData.at(0).price == "2.5543");

    REQUIRE(responseData.at(1).ticker == "BTC");
    REQUIRE(responseData.at(1).price == "101994.6643");
}

TEST_CASE("apiResponse_constructedFromJson_multipleCryptos_defaultCurrency_verbose", "[unit][api-response][json-parsing][multiple-cryptos]") {
    auto mockResponse = R"({
        "data": {
            "XRP": {
                "quote": {
                    "EUR": {
                        "price": 2.5543,
                        "volume_24h": 6645731238.931866,
					    "percent_change_1h": -0.00963765,
					    "percent_change_24h": -5.80800291,
                        "market_cap": 126977832119.58655
                    }
                }
            }
        }
    })"_json;

    CommandLineParser mockParser;
    char arg1[] = "crypto-fetch";
    char arg2[] = "-vt";
    char arg3[] = "XRP";
    char* mockArgs[] = {arg1, arg2, arg3};
    mockParser.parse(3, mockArgs);

    ApiResponse response{mockParser, mockResponse};
    const std::vector<ResponseData> responseData = response.getResponses();
    REQUIRE(responseData.size() == 1);
    REQUIRE(response.isVerbose() == true);

    REQUIRE(responseData.at(0).ticker == "XRP");
    REQUIRE(responseData.at(0).price == "2.5543");
    REQUIRE(responseData.at(0).marketCap == "126977832119.58655");
    REQUIRE(responseData.at(0).volume24hr == "6645731238.931866");
    REQUIRE(responseData.at(0).percentChange1hr == "-0.00963765");
    REQUIRE(responseData.at(0).percentChange24hr == "-5.80800291");
}
