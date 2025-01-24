/**
 * @file Formatter.hpp
 * @author liam 
 * @date 10/01/2025
 */

#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include "ApiResponse.hpp"

namespace cf {
    class Formatter {
    public:
        Formatter() = default;
        ~Formatter() = default;

        static void display(const ApiResponse& response);

    private:
        static void displayNormal(const ApiResponse& response);
        static void displayVerbose(const ApiResponse& response);

        static std::string getCurrencySymbol(std::string_view currency);
        static std::string getCurrentTimestamp();
        static std::string formatNumber(const std::string& numStr, std::string_view currencySymbol, int precision = 2);
        static std::string formatLargeNumber(const std::string& numStr, std::string_view currencySymbol);
        static std::string formatPercentage(const std::string& numStr, int precision = 2);
    };
} // namespace cf

#endif //FORMATTER_HPP
