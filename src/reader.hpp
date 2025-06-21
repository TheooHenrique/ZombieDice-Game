
#ifndef READER_HPP
#define READER_HPP

#include <map>
#include <string>

class Reader {
public:
    Reader(const std::string& filename);
    std::map<std::string, std::string> getSection(const std::string& section);

private:
    std::map<std::string, std::map<std::string, std::string>> data;
};

#endif
