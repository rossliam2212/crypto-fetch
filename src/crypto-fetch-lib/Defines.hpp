/**
 * @file Defines.hpp
 * @author liam 
 * @date 07/01/2025
 */

#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <string>

inline const char* API_KEY_ENVIRONMENT_VAR = "COINMARKETCAP_API_KEY";
const std::string FALLBACK_API_KEY_LOCATION{"../api_key.txt"};

const std::string CMD_TICKER{"ticker"};
const std::string CMD_CURRENCY{"currency"};
const std::string CMD_HELP{"help"};
const std::string CMD_VERSION{"version"};
const std::string CMD_VERBOSE{"verbose"};

constexpr std::string_view EUR_CODE{"EUR"};
constexpr std::string_view GBP_CODE{"GBP"};
constexpr std::string_view USD_CODE{"USD"};
constexpr std::string_view CAD_CODE{"CAD"};
constexpr std::string_view AUD_CODE{"AUD"};
constexpr std::string_view NZD_CODE{"NZD"};
constexpr std::string_view HKD_CODE{"HKD"};

const std::string DEFAULT_CURRENCY{EUR_CODE};
constexpr int FLOATING_POINT_PRECISION{4};

const std::string EURO_SYMBOL{"€"};
const std::string DOLLAR_SYMBOL{"$"};
const std::string POUND_SYMBOL{"£"};

const std::string API_BASE_URL{"https://pro-api.coinmarketcap.com"};
const std::string API_LATEST_ENDPOINT{"/v1/cryptocurrency/quotes/latest"};
const std::string API_SYMBOL_ARG{"?symbol="};
const std::string API_CONVERT_ARG{"&convert="};

constexpr char HEADER_API_KEY[] = "X-CMC_PRO_API_KEY";
constexpr char HEADER_ACCEPT[] = "Accept: application/json";


#endif //DEFINES_HPP
