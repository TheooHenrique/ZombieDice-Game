#ifndef ZDICE_HPP
#define ZDICE_HPP

#include <random>
#include <string>
class ZDice{
    using size_type = size_t;
    public:
    ///Constructor
    ZDice(bool green, bool yellow, bool red, std::string faces);

    //METHODS
    std::string roll();

    ///GET METHODS
    const std::string get_faces(){ return faces; }
    const std::string get_result(){ return roll_result; }

    ///SET METHODS:
    void set_faces(std::string f){ faces = f; }

    private:
    //ATTRIBUTES
    bool m_green; 
    bool m_yellow; //O que estiver como "true" indica o que o dado é. Esses bools definem os valores da string "faces" em zdice.cpp
    bool m_red;
    std::string faces;
    std::string roll_result;
    mutable std::mt19937 gen;
};

#endif