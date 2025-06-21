#ifndef ZDICE_HPP
#define ZDICE_HPP

#include <string>
#include <cstdint>
class ZDice{
    private:
    bool m_green;
    bool m_yellow;
    bool m_red;
    mutable std::mt19937 gen;

    public:
    ///Constructor
    ZDice(const std::string& faces); 
    std::string roll();
};

#endif