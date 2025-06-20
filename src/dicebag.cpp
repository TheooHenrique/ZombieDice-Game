#include "dicebag.hpp"
#include <algorithm>
#include <random>
#include <iostream>

ZDice_Bag::ZDice_Bag(int green, int yellow, int red, const std::string& weak_faces, const std::string& strong_faces, const std::string& tough_faces) : weak_faces(weak_faces), strong_faces(strong_faces), tough_faces(tough_faces) {
    for (int i = 0; i < green; ++i) available_dice.push_back("weak");
    for (int i = 0; i < yellow; ++i) available_dice.push_back("strong");
    for (int i = 0; i < red; ++i) available_dice.push_back("tough");
}

std::string ZDice_Bag::sort_dices(int num_dice) {
    if (available_dice.size() < num_dice) {
        refill();
    }

    std::random_shuffle(available_dice.begin(), available_dice.end());
    std::string result;

    for (size_t i {0}; i < num_dice; ++i) {
        result += available_dice.back().substr(0,1); //get the first letter (w, s, t)
        used_dice.push_back(available_dice.back());
        available_dice.pop_back();
    }

    return result;
}

void ZDice_Bag::refill() {
    available_dice.insert(available_dice.end(), used_dice.begin(), used_dice.end()); //inserts at the end of available_dice all the elements of the range that goes from the beginning to the end of the used_dice vector.
    used_dice.clear();
}

int ZDice_Bag::verifyNumberDices() {
    return available_dice.size();
}