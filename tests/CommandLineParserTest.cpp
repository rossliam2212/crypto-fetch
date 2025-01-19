/**
 * @file CommandLineParserTest.cpp
 * @author liam
 * @date 18/01/2025
 */

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include "CommandLineParser.hpp"

TEST_CASE("commandLineParser_singleTickerDefaultCurrency_parsesOptionsCorrectly",
          "[unit][command-line-parser][option-parsing]") {
    char arg1[] = "crypto-fetch";
    char arg2[] = "-t";
    char arg3[] = "XRP";
    char* mockArgs[] = {arg1, arg2, arg3};

    CommandLineParser parser;
    parser.parse(3, mockArgs);

    REQUIRE(parser.getTickers().size() == 1);
    REQUIRE(parser.getCurrency() == "EUR");
    REQUIRE(parser.isVerbose() == false);
}

TEST_CASE("commandLineParser_multipleTickersDefaultCurrency_parsesOptionsCorrectly", "[unit][command-line-parser][option-parsing]") {
    char arg1[] = "crypto-fetch";
    char arg2[] = "-t";
    char arg3[] = "XRP,BTC,XLM";
    char* mockArgs[] = {arg1, arg2, arg3};

    CommandLineParser parser;
    parser.parse(3, mockArgs);

    REQUIRE(parser.getTickers().size() == 3);
    REQUIRE(parser.getTickers().at(0) == "XRP");
    REQUIRE(parser.getTickers().at(1) == "BTC");
    REQUIRE(parser.getTickers().at(2) == "XLM");
    REQUIRE(parser.getCurrency() == "EUR");
    REQUIRE(parser.isVerbose() == false);
}

TEST_CASE("commandLineParser_singleTickerSpecifiedCurrencyVerbose_parsesOptionsCorrectly", "[unit][command-line-parser][option-parsing]") {
    char arg1[] = "crypto-fetch";
    char arg2[] = "-vt";
    char arg3[] = "XRP";
    char arg4[] = "-c";
    char arg5[] = "USD";
    char* mockArgs[] = {arg1, arg2, arg3, arg4, arg5};

    CommandLineParser parser;
    parser.parse(5, mockArgs);

    REQUIRE(parser.getTickers().size() == 1);
    REQUIRE(parser.getTickers().at(0) == "XRP");
    REQUIRE(parser.getCurrency() == "USD");
    REQUIRE(parser.isVerbose() == true);
}

TEST_CASE("commandLineParser_noTickerSpecified_exceptionThrown", "[unit][command-line-parser][option-parsing]") {
    const std::string EXPECTED_MESSAGE = "CMD parsing error - Ticker option not specified";

    char arg1[] = "crypto-fetch";
    char arg2[] = "XRP";
    char* mockArgs[] = {arg1, arg2};

    CommandLineParser parser;
    REQUIRE_THROWS_AS(parser.parse(2, mockArgs), std::runtime_error);
    REQUIRE_THROWS_WITH(parser.parse(2, mockArgs), EXPECTED_MESSAGE);
}

TEST_CASE("commandLineParser_invalidOptionSpecified_exceptionThrown", "[unit][command-line-parser][option-parsing]") {
    const std::string EXPECTED_MESSAGE = "CMD parsing error - Option 's' does not exist";

    char arg1[] = "crypto-fetch";
    char arg2[] = "-st";
    char arg3[] = "XRP";
    char* mockArgs[] = {arg1, arg2, arg3};

    CommandLineParser parser;
    REQUIRE_THROWS_AS(parser.parse(2, mockArgs), std::runtime_error);
    REQUIRE_THROWS_WITH(parser.parse(2, mockArgs), EXPECTED_MESSAGE);
}