/**
 * @file Formatter.cpp
 * @author liam 
 * @date 10/01/2025
 */

#include "cf/Formatter.hpp"

namespace cf {
    void Formatter::display(const ApiResponse& response) {
        if (response.isVerbose()) {
            displayVerbose(response);
        } else {
            displayNormal(response);
        }
    }

    void Formatter::displayNormal(const ApiResponse& response) {
        const auto responses = response.getResponses();
        const std::string timestamp = getCurrentTimestamp();

        fmt::println("{:-^30}", project_name);

        for (auto& r : responses) {
            const std::string ticker = fmt::format("{}{}", DOLLAR_SYMBOL, r.ticker);
            const std::string currencySymbol = getCurrencySymbol(r.currency);
            const std::string formattedPrice = formatNumber(r.price, currencySymbol, FLOATING_POINT_PRECISION);

            fmt::println("| {:<11} | {:>12} |", "Ticker", ticker);
            if (currencySymbol == DOLLAR_SYMBOL) {
                if (r.currency == USD_CODE) {
                    fmt::println("| {:<11} | {:>12} |", "Price", formattedPrice);
                } else {
                    fmt::println("| {:<6}({:<}) | {:>12} |", "Price", r.currency, formattedPrice);
                }
            } else {
                fmt::println("| {:<11} | {:>12} |", "Price", formattedPrice);
            }
            fmt::println("{:-^30}", "");
        }

        fmt::println("| {:<11} | {:>12} |", "Timestamp", timestamp);
        fmt::println("{:-^30}\n", "");
    }

    void Formatter::displayVerbose(const ApiResponse& response) {
        const auto responses = response.getResponses();
        const std::string timestamp = getCurrentTimestamp();

        fmt::println("{:-^32}", project_name);

        for (auto& r : responses) {
            const std::string ticker = fmt::format("{}{}", DOLLAR_SYMBOL, r.ticker);
            const std::string currencySymbol = getCurrencySymbol(r.currency);
            const std::string formattedPrice = formatNumber(r.price, currencySymbol, FLOATING_POINT_PRECISION);
            const std::string marketCap = formatLargeNumber(r.marketCap, currencySymbol);
            const std::string volume24hr = formatLargeNumber(r.volume24hr, currencySymbol);
            const std::string percentageChange1hr = formatPercentage(r.percentChange1hr, FLOATING_POINT_PRECISION);
            const std::string percentageChange24hr = formatPercentage(r.percentChange24hr, FLOATING_POINT_PRECISION);

            // ---
            // Ticker & Price
            fmt::println("| {:<13} | {:>12} |", "Ticker", ticker);
            if (currencySymbol == DOLLAR_SYMBOL) {
                if (r.currency == USD_CODE) {
                    fmt::println("| {:<13} | {:>12} |", "Price", formattedPrice);
                } else {
                    fmt::println("| {:<6}({:<}) | {:>12} |", "Price", r.currency, formattedPrice);
                }
            } else {
                fmt::println("| {:<13} | {:>12} |", "Price", formattedPrice);
            }
            fmt::println("{:-^32}", "");

            // ---
            // Market Cap
            fmt::println("| {:<13} | {:>12} |", "MarketCap", marketCap);
            fmt::println("{:-^32}", "");

            // ---
            // 24 Hour Volume
            fmt::println("| {:<13} | {:>12} |", "24hr Vol", volume24hr);
            fmt::println("{:-^32}", "");

            // ---
            // 1hr Percentage Change & 1hr Percentage Change
            fmt::println("|  {:<12} | {:>12} |", "1hr % Change", percentageChange1hr);
            fmt::println("| {:<13} | {:>12} |", "24hr % Change", percentageChange24hr);
            fmt::println("{:-^32}", "");
        }
        fmt::println("| {:<13} | {:>12} |", "Timestamp", timestamp);
        fmt::println("{:-^32}\n", "");
    }

    std::string Formatter::getCurrencySymbol(const std::string_view currency) {
        static const std::unordered_map<std::string_view, std::string> currencyToSymbol = {
            {EUR_CODE, EURO_SYMBOL},
            {GBP_CODE, POUND_SYMBOL},
            {USD_CODE, DOLLAR_SYMBOL},
            {CAD_CODE, DOLLAR_SYMBOL},
            {AUD_CODE, DOLLAR_SYMBOL},
            {NZD_CODE, DOLLAR_SYMBOL},
            {HKD_CODE, DOLLAR_SYMBOL},
        };

        auto iter = currencyToSymbol.find(currency);
        if (iter != std::end(currencyToSymbol)) {
            return iter->second;
        }

        return EURO_SYMBOL;
    }

    std::string Formatter::getCurrentTimestamp() {
        const auto now = std::chrono::system_clock::now();
        const std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        const std::tm now_tm = *std::localtime(&now_c); // convert to local time

        std::ostringstream timestamp;
        timestamp << std::put_time(&now_tm, "%d %b %H:%M");

        return timestamp.str();
    }

    std::string Formatter::formatNumber(const std::string& numStr, const std::string_view currencySymbol, int precision) {
        const double number = std::stod(numStr);
        return fmt::format("{}{:.{}f}", currencySymbol, number, precision);
    }

    std::string Formatter::formatLargeNumber(const std::string& numStr, const std::string_view currencySymbol) {
        try {
            double number = std::stod(numStr);
            const char* suffix = "";

            if (number >= 1e12) {
                number /= 1e12;
                suffix = "T"; // trillions
            } else if (number >= 1e9) {
                number /= 1e9;
                suffix = "B"; // billions
            } else if (number >= 1e6) {
                number /= 1e6;
                suffix = "M"; // millions
            } else if (number >= 1e3) {
                number /= 1e3;
                suffix = "K"; // thousands
            }
            return fmt::format("{}{:.1f}{}", currencySymbol, number, suffix);
        } catch (const std::exception&) {
            return "null";
        }
    }

    std::string Formatter::formatPercentage(const std::string& numStr, int precision) {
        const double number = std::stod(numStr);
        return fmt::format("{:.{}f}%", number, precision);
    }
} // namespace cf
