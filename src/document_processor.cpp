#include "../include/document_processor.hpp"

#include <filesystem>
#include <iostream>
#include <unordered_map>

#include "../include/lexer.hpp"
#include "../include/xml_parser.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;
using namespace std;

// process all XML files in the given directory and count word frequencies for each file
unordered_map<fs::path, unordered_map<std::string, size_t>> process_documents(
    const std::string& dir_path) {
    unordered_map<fs::path, unordered_map<std::string, size_t>> all_documents;

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
                unordered_map<std::string, size_t> frequency_table;

                std::optional<std::string_view> token;
                while ((token = lexer.next_token())) {
                    std::string tokenStr(token->data(), token->size());

                    // increment frequency count for each token
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

    return all_documents;
}

json generate_index_json(
    const unordered_map<fs::path, unordered_map<string, size_t>>& all_documents) {
    json index_json;  // json where will be stored

    for (const auto& doc : all_documents) {
        // pair to preserve the order
        vector<std::pair<string, size_t>> freq_vec(doc.second.begin(), doc.second.end());
        std::sort(freq_vec.begin(), freq_vec.end(),
                  [](const auto& a, const auto& b) { return a.second > b.second; });

        // will hold -> "term": "foo", "frequency": 420
        json top_terms = json::array();

        // get the 10 most repeated words
        size_t top_ten = 0;
        for (const auto& term : freq_vec) {
            top_terms.push_back({{"term", term.first}, {"frequency", term.second}});
            top_ten++;
            if (top_ten >= 10) break;
        }

        // path to file: {ten most frequent terms}
        index_json[doc.first.string()] = top_terms;
    }

    return index_json;
}
