/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** DLLoader
*/

#pragma once

#include <memory>
#include <dlfcn.h>
#include <iostream>

/// @brief Dynamic library loader
class DLLoader {
    public:

        /// @brief Loading mode
        typedef enum {
            /// @brief Lazy loading
            LAZY = RTLD_LAZY,
            /// @brief Immediate loading
            NOW = RTLD_NOW,
            /// @brief Local loading
            LOCAL = RTLD_LOCAL,
            /// @brief Global loading
            GLOBAL = RTLD_GLOBAL,
            /// @brief No delete loading
            NODELETE = RTLD_NODELETE,
            /// @brief No load loading
            NOLOAD = RTLD_NOLOAD
        } LoadingMode;

        /**
         * @brief Construct a new DLLoader object
         * @param filepath Path to the library
         */
        DLLoader(const std::string &filepath, LoadingMode mode = LAZY);

        /**
         * @brief Destroy the DLLoader object
         */
        ~DLLoader();

        /**
         * @brief Open the library
         * @param filepath Path to the library
         * @param mode Loading mode
         */
        static std::shared_ptr<DLLoader> open(const std::string &filepath, LoadingMode mode = LAZY);

        /**
         * @brief Get a function from the library
         * @tparam T Function prototype
         * @param name Symbol name
         * @return T Function founded
         */
        template <typename T>
        T loadSymbol(std::string name) {
            if (!this->_handle)
                throw DLLoaderExeption("Library not loaded");
            T symbol = reinterpret_cast<T>(dlsym(this->_handle, name.c_str()));
            if (!symbol)
                this->_throwError();
            return symbol;
        }

        /// @brief Exception class
        class DLLoaderExeption : public std::exception {
            public:

                /**
                 * @brief Construct a new DLLoaderExeption object
                 * @param message Error message
                 */
                DLLoaderExeption(const std::string &message);

                const char *what() const noexcept override;

            private:
                const std::string _message;
        };

    private:
        void *_handle;
        std::string _filepath;

        /**
         * @brief Throw an error
         */
        void _throwError();
};
