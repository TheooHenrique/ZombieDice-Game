#ifndef ZDICE_HPP
#define ZDICE_HPP

#include <random>
#include <string>
class ZDice{
    private:
    bool m_green; //O que estiver como "true" indica o que o dado é. São esses bools que devem definir o valor de "faces"
    bool m_yellow;
    bool m_red;
    mutable std::mt19937 gen;

    public:
    ///Constructor
    ZDice(const std::string& faces); 

    std::string faces;
    std::string roll();
};

#endif