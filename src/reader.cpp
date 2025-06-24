#include "reader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

// Helper function to remove whitespace at the beginning and end of the string
void trim(std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) ++start;
    auto end = s.end();
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    s.assign(start, end + 1);
}

void remove_quotes(std::string& s) {
    if (s.length() >= 2 && s.front() == '"' && s.back() == '"') {
        s.erase(0, 1);
        s.erase(s.length() - 1, 1);
    }
}

Reader::Reader(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, section;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == ';' || line[0] == '#') continue;
        
        if (line[0] == '[') {
            size_t end = line.find(']');
            if (end != std::string::npos) {
                section = line.substr(1, end - 1); //extracts the section. in the case of our .ini, it can extract Game or Dice
                trim(section);
            }
        } else {
            size_t eq {line.find('=')};
            if (eq != std::string::npos) {
                std::string key = line.substr(0, eq); //everything before =
                std::string val = line.substr(eq + 1); //everything after =
                trim(key);
                trim(val);
                remove_quotes(val);
                data[section][key] = val;
            }
        }
    }
}

const std::map<std::string, std::string>& Reader::getSection(const std::string& section) const {
    return data.at(section);
}