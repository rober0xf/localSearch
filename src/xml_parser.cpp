#include "../include/xml_parser.hpp"

#include <iostream>
#include <ostream>
#include <pugixml.hpp>
#include <sstream>

std::string parse_xml_file(const std::string& path) {
    pugi::xml_document doc;

    // ::load_file takes a char*
    if (!doc.load_file(path.c_str())) {
        std::cerr << "ERROR loading file: " << path << std::endl;
        return {};
    }

    std::stringstream ss;
    doc.save(ss);

    return ss.str();
}
