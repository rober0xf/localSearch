#ifndef LEXER_HPP
#define LEXER_HPP

#include <cctype>
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <optional>
#include <string_view>

class Lexer {
    private:
        // reference to the vec of chars
        std::string_view content;

        size_t current_pos;

        // skip whitespaces
        void trim_left();

    public:
        // store the reference and initilize it. also prevents implicit type conversion
        explicit Lexer(std::string_view content);

        std::optional<std::string_view> next_token();
        std::optional<std::string_view> next();

        // iterator for the lexer
        class iterator {
            private:
                Lexer* lexer;  // the lexer we are iterating over
                std::optional<std::string_view> current_token;

            public:
                // constructor. if not lexer provided takes nullptr
                iterator(Lexer* lexer = nullptr);

                bool operator!=(const iterator& other) const;
                iterator& operator++();

                // dereference. returns the current token value
                std::string_view operator*() const;
        };

        // returns an iterator pointing to the first element
        iterator begin();

        // return a past-the-end iterator
        iterator end();
};

#endif /* LEXER_HPP */
