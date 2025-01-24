/**
 * @file ApiKeyException.hpp
 * @author liam 
 * @date 24/01/2025
 */

#ifndef APIKEYEXCEPTION_HPP
#define APIKEYEXCEPTION_HPP

#include <string>
#include <exception>

namespace cf {
    class ApiKeyException final : public std::exception {
    public:
        ApiKeyException(const char* message);
        ApiKeyException(const std::string& message);
        ~ApiKeyException() override = default;

        const char* what() const noexcept override;

    private:
        const char* message;
    };
} // namespace cf

#endif //APIKEYEXCEPTION_HPP
