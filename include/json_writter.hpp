#ifndef JSON_WRITER_HPP
#define JSON_WRITER_HPP

#include <json.hpp>
#include <string>

bool write_json_to_file(const std::string& file_path, const nlohmann::json& json_data);

#endif  // JSON_WRITER_HPP
