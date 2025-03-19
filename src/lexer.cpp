#include "../include/lexer.hpp"

#include <cctype>
#include <string>

// constructor implementation
Lexer::Lexer(std::string_view content) : content(content), current_pos(0){};

void Lexer::trim_left() {
    while (current_pos < content.size() && std::isspace(content[current_pos])) {
        current_pos++;
    }
}

std::optional<std::string_view> Lexer::next_token() {
    trim_left();
    if (current_pos >= content.size()) {
        return std::nullopt;  // end of input
    }

    size_t start = current_pos;

    if (std::isalnum(content[current_pos])) {
        while (current_pos < content.size() && std::isalnum(content[current_pos])) {
            current_pos++;
        }
        return std::string_view(content.data() + start, current_pos - start);
    }

    if (content[current_pos] == '<') {
        size_t tag_start = current_pos;
        bool closing_tag =
            (current_pos + 1 < content.size() && content[current_pos + 1] == '/');
        current_pos++;

        // find the tag name
        std::string tag_name;
        while (current_pos < content.size() && !std::isspace(content[current_pos]) &&
               content[current_pos] != '>') {
            if (content[current_pos] != '/') {
                tag_name.push_back(content[current_pos]);
            }
            current_pos++;
        }

        // skip to the end of the tag
        while (current_pos < content.size() && content[current_pos] != '>') {
            current_pos++;
        }

        if (current_pos < content.size()) {
            current_pos++;  // skip the closing >
        }

        return next_token();
    }

    size_t text_start = current_pos;
    while (current_pos < content.size() && content[current_pos] != '<') {
        current_pos++;
    }

    std::string_view text_content(content.data() + text_start, current_pos - text_start);

    // trim whitespaces
    size_t ws_start = 0;
    while (ws_start < content.size() && isspace(text_content[ws_start])) {
        ws_start++;
    }

    size_t ws_end = text_content.size();
    while (ws_end > ws_start && isspace(text_content[ws_end - 1])) {
        ws_end--;
    }

    std::string_view trimmed_content = text_content.substr(ws_start, ws_end - ws_start);
    if (trimmed_content.empty()) {
        return next_token();
    }

    return trimmed_content;
}

// for the iterator
std::optional<std::string_view> Lexer::next() {
    return next_token();
}

// iterator constructor
Lexer::iterator::iterator(Lexer* lexer) : lexer(lexer) {
    if (lexer) {
        current_token = lexer->next();
    }
}

bool Lexer::iterator::operator!=(const Lexer::iterator& other) const {
    return (lexer != other.lexer) ||
           (current_token.has_value() != other.current_token.has_value());
}

Lexer::iterator& Lexer::iterator::operator++() {
    if (lexer) {
        current_token = lexer->next();
    }
    return *this;
}

std::string_view Lexer::iterator::operator*() const {
    return current_token.value();
}

Lexer::iterator Lexer::begin() {
    return iterator(this);
}

Lexer::iterator Lexer::end() {
    return iterator();
}
