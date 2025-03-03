#include <cstring>
#include <iosfwd>
#include <iostream>
#include <ostream>
#include <pugixml.hpp>
#include <string>

void parse_xml_file(const std::string& path);
void read_node(const pugi::xml_node& node);

int main() {
    std::string file_path = "docs.gl/gl3/glPixelStore.xhtml";
    parse_xml_file(file_path);

    return 0;
}

void parse_xml_file(const std::string& path) {
    pugi::xml_document doc;
    pugi::xml_parse_result result =
        doc.load_file(path.c_str());  // ::load_file takes a char*
    if (!result) {
        std::cerr << "ERROR: " << result.description() << std::endl;
    }

    read_node(doc.document_element());
}

void read_node(const pugi::xml_node& node) {
    for (const pugi::xml_node& child : node.children()) {
        if (std::string(child.child_value()).empty() && child.first_attribute().empty() &&
            std::string(child.value()).empty()) {
            continue;
        }
        for (const pugi::xml_attribute& attr : child.attributes()) {
            std::cout << attr.name() << ": " << attr.value() << " ";
        }
        std::cout << child.text().as_string() << std::endl;

        // read_node(child);
    }
}
