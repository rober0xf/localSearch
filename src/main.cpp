#include <algorithm>
#include <cstddef>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <json.hpp>
#include <ostream>
#include <pugixml.hpp>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../include/lexer.hpp"

template <typename Key, typename Value>
using unordered_map = std::unordered_map<Key, Value>;

std::string parse_xml_file(const std::string& path);
unordered_map<std::string, size_t> index_document(std::string content);

namespace fs = std::filesystem;
using json = nlohmann::json;
int main() {
    unordered_map<fs::path, unordered_map<std::string, size_t>> all_documents;
    std::string dir_path = "docs.gl/gl4";

    json index_json;
    for (const auto& entry : fs::directory_iterator(dir_path)) {
        if (entry.is_regular_file()) {
            fs::path file_path = entry.path();
            std::cout << "processing file: " << file_path << std::endl;

            try {
                std::string content = parse_xml_file(file_path.string());
                if (content.empty()) {
                    continue;
                }

                Lexer lexer(content);
                std::unordered_map<std::string, size_t> frequency_table;

                std::optional<std::string_view> token;
                while ((token = lexer.next_token())) {
                    std::string tokenStr(token->data(), token->size());
                    frequency_table[tokenStr]++;
                }

                all_documents[file_path] = std::move(frequency_table);
            } catch (const std::exception& e) {
                std::cerr << "exception processing file: " << e.what() << std::endl;
                std::cerr << "file: " << file_path << std::endl;
                continue;
            }
        }
    }

    for (const auto& doc : all_documents) {
        std::cout << "file: " << doc.first << std::endl;
        std::vector<std::pair<std::string, size_t>> freq_vec(doc.second.begin(),
                                                             doc.second.end());
        std::sort(freq_vec.begin(), freq_vec.end(),
                  [](const auto& a, const auto& b) { return a.second > b.second; });
        json top_terms = json::array();
        size_t top_ten = 0;
        for (const auto& term : freq_vec) {
            std::cout << "  " << term.first << "--> " << term.second << std::endl;
            top_terms.push_back({{"term", term.first}, {"frequency", term.second}});
            top_ten++;
            if (top_ten >= 10) break;
        }

        index_json[doc.first] = top_terms;
        std::cout << std::endl;
    }

    std::ofstream output_file("index.json");
    if (output_file.is_open()) {
        output_file << index_json.dump(4);  // pretty print 4 spaces
        output_file.close();
        std::cout << "JSON written successfully" << std::endl;
    } else {
        std::cerr << "failed to writing JSON file" << std::endl;
    }

    return 0;
}

std::string parse_xml_file(const std::string& path) {
    pugi::xml_document doc;

    // ::load_file takes a char*
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    if (!result) {
        std::cerr << "ERROR: " << result.description() << std::endl;
        return {};
    }

    std::stringstream ss;
    doc.save(ss);

    return ss.str();
}
