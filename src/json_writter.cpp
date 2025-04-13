#include "../include/json_writter.hpp"

#include <fstream>
#include <iostream>

// check if the generate_index_json was done correctly
bool write_json_to_file(const std::string& file_path, const nlohmann::json& json_data) {
    std::ofstream output_file(file_path);

    if (output_file.is_open()) {
        output_file << json_data.dump(4);  // 4 spaces
        output_file.close();
        return true;
    } else {
        std::cerr << "failed to open file: " << file_path << std::endl;
        return false;
    }
}
