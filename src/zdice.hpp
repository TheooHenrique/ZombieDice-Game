#ifndef ZDICE_HPP
#define ZDICE_HPP

#include <string>
#include <vector>
#include <cstdint>

class ZDice{
public:
    ///Constructor
    ZDice(const std::string& faces); 
    char roll();

private:
    std::string faces;
    mutable std::mt19937 gen;
};

#endif