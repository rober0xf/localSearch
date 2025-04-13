#ifndef DOCUMENT_PROCESSOR_HPP
#define DOCUMENT_PROCESSOR_HPP

#include <filesystem>
#include <json.hpp>
#include <string>
#include <unordered_map>

std::unordered_map<std::filesystem::path, std::unordered_map<std::string, size_t>>
process_documents(const std::string& dir_path);

nlohmann::json generate_index_json(
    const std::unordered_map<std::filesystem::path,
                             std::unordered_map<std::string, size_t>>& all_documents);

#endif  // DOCUMENT_PROCESSOR_HPP
