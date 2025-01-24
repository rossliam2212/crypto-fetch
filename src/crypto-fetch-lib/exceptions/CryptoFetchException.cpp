/**
 * @file CryptoFetchException.cpp
 * @author liam 
 * @date 24/01/2025
 */

#include "cf/exceptions/CryptoFetchException.hpp"

namespace cf {
    CryptoFetchException::CryptoFetchException(const char* message)
        : message{message} {
    }

    CryptoFetchException::CryptoFetchException(const std::string& message)
        : message{message.c_str()} {
    }

    const char* CryptoFetchException::what() const noexcept {
        return message;
    }
} // namespace cf