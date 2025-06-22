#include "zdice.hpp"
#include <algorithm>
#include <random>
#include <string>
using size_type = size_t;

ZDice::ZDice(bool green, bool yellow, bool red) { 
    ///initializes the member variable faces (the one on the left) with the value of the parameter faces (the one on the right).
    // When you create a ZDice object dice("ABC");, the internal variable dice.faces receives the value "ABC".
    m_green = green;
    m_yellow = yellow;
    m_red = red;
    if (m_green){faces = "bbbffs";} 
    else if ( m_yellow ){ faces = "bbffss"; }
    else if ( m_red ){ faces = "bffsss"; }
    std::random_device rd;
    gen = std::mt19937(rd());
}


size_type i = 0;
std::string ZDice::roll() {
    std::shuffle(faces.begin(), faces.end(), gen);
    std::string s(1, faces[i]); //Converte o char i em string
    ++i;
    return s;
}