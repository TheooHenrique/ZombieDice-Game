#include "zdice.hpp"
#include <algorithm>
#include <random>
#include <string>
#include <chrono>
using size_type = size_t;

ZDice::ZDice(bool green, bool yellow, bool red, std::string all_faces) { 
    m_green = green;
    m_yellow = yellow;
    m_red = red;
    faces = all_faces;
    std::random_device rd;
    gen = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());
}

std::string ZDice::roll() {
    std::shuffle(faces.begin(), faces.end(), gen);
    roll_result = faces[0]; 
    
    return roll_result;
}