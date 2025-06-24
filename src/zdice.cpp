#include "zdice.hpp"
#include <algorithm>
#include <random>
#include <string>
using size_type = size_t;

ZDice::ZDice(bool green, bool yellow, bool red, std::string all_faces) { 
    m_green = green;
    m_yellow = yellow;
    m_red = red;
    faces = all_faces;
    std::random_device rd;
    gen = std::mt19937(rd());
}

size_type i = 0;
std::string ZDice::roll() {
    std::shuffle(faces.begin(), faces.end(), gen);
    roll_result = faces[i]; //Converte o char i em string
    
    return roll_result;
}