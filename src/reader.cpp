/**
 * @file reader.cpp
 * @brief Implementation of the Reader class for parsing .ini files.
 * @author Haniel Lucas Machado Rocha
 * @author Theo Henrique da Silva Borges
 * @date June 24th, 2025
 */

#include "reader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Removes leading and trailing whitespace from a string.
 * @param s The string to be trimmed. The operation is done in-place.
 */
void trim(std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) ++start;
    auto end = s.end();
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    s.assign(start, end + 1);
}

/**
 * @brief Removes leading and trailing double quotes from a string.
 * @param s The string to be modified. The operation is done in-place.
 */
void remove_quotes(std::string& s) {
    if (s.length() >= 2 && s.front() == '"' && s.back() == '"') {
        s.erase(0, 1);
        s.erase(s.length() - 1, 1);
    }
}

/**
 * @brief Constructs a Reader object and parses the specified file.
 *
 * This constructor opens and reads the given file line by line. It parses
 * section headers (e.g., `[Section]`), key-value pairs (e.g., `key = value`),
 * and ignores empty lines or lines starting with ';' or '#' (comments).
 * All parsed data is stored in the `data` member variable.
 *
 * @param filename The path to the configuration file.
 */
Reader::Reader(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, section;

    // Ignore empty lines and comments
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == ';' || line[0] == '#') continue;
        
        // Check for a section header
        if (line[0] == '[') {
            size_t end = line.find(']');
            if (end != std::string::npos) {
                section = line.substr(1, end - 1); //extracts the section. in the case of our .ini, it can extract Game or Dice
                trim(section);
            }
        } else { //it's a key-value pair
            size_t eq {line.find('=')};
            if (eq != std::string::npos) {
                std::string key = line.substr(0, eq); //everything before =
                std::string val = line.substr(eq + 1); //everything after =
                trim(key);
                trim(val);
                remove_quotes(val); // Remove quotes if they exist
                data[section][key] = val;
            }
        }
    }
}

const std::map<std::string, std::string>& Reader::getSection(const std::string& section) const {
    return data.at(section);
}