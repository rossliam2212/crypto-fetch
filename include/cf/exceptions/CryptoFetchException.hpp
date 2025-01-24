/**
 * @file CryptoFetchException.hpp
 * @author liam 
 * @date 24/01/2025
 */

#ifndef CRYPTOFETCHEXCEPTION_HPP
#define CRYPTOFETCHEXCEPTION_HPP

#include <string>
#include <exception>

namespace cf {
    class CryptoFetchException : public std::exception{
    public:
        CryptoFetchException(const char* message);
        CryptoFetchException(const std::string& message);
        ~CryptoFetchException() override = default;

        const char* what() const noexcept override;

    private:
        const char* message;
    };
} // namespace cf

#endif //CRYPTOFETCHEXCEPTION_HPP
