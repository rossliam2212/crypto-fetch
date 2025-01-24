/**
 * @file ApiKeyException.cpp
 * @author liam 
 * @date 24/01/2025
 */

#include "cf/exceptions/ApiKeyException.hpp"

namespace cf {
    ApiKeyException::ApiKeyException(const char* message)
        : message{message} {
    }

    ApiKeyException::ApiKeyException(const std::string& message)
        : message{message.c_str()} {
    }

    const char* ApiKeyException::what() const noexcept {
        return message;
    }
} // namespace cf