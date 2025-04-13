#include <iostream>
#include <string>

#include "../include/document_processor.hpp"
#include "../include/json_writter.hpp"

int main() {
    std::string dir_path = "data/docs.gl/gl4";
    std::cout << "processing document..." << std::endl;

    auto all_documents = process_documents(dir_path);
    auto index_json = generate_index_json(all_documents);

    if (write_json_to_file("index.json", index_json)) {
        std::cout << "JSON written successfully" << std::endl;
    } else {
        std::cerr << "failed to write JSON file" << std::endl;
    }

    return 0;
}
