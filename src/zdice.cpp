#include "zdice.hpp"
#include <random>
#include <string>

ZDice::ZDice(const std::string& faces) : faces(faces) { 
    ///initializes the member variable faces (the one on the left) with the value of the parameter faces (the one on the right).
    // When you create a ZDice object dice("ABC");, the internal variable dice.faces receives the value "ABC".
    std::random_device rd;
    gen = std::mt19937(rd());
}

std::string ZDice::roll() {
    std::uniform_int_distribution<> dist(0, faces.size() - 1);
    return faces[dist(gen)];
}