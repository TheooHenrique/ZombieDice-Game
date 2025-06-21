#include "dicebag.hpp"
#include <algorithm>
#include <random>
#include <iostream>
using size_type = size_t;

DiceBag::DiceBag(size_type green, size_type yellow, size_type red, size_type total){
    m_green_amount = green;
    m_yellow_amount = yellow;
    m_red_amount = red;
    m_total_dices = total;
    for (int i = 0; i < green; ++i) available_dice.push_back("weak");
    for (int i = 0; i < yellow; ++i) available_dice.push_back("strong");
    for (int i = 0; i < red; ++i) available_dice.push_back("tough");
}

std::string DiceBag::sort_dices(int num_dice) {
    if (available_dice.size() < num_dice) {
        refill_bag();
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

size_type DiceBag::refill_bag() {
    available_dice.insert(available_dice.end(), used_dice.begin(), used_dice.end()); //inserts at the end of available_dice all the elements of the range that goes from the beginning to the end of the used_dice vector.
    used_dice.clear();
}

size_type DiceBag::lower_than_3_dices() {
    return available_dice.size(); //Acho que essa função seria melhor encaixada como retornando um bool (true se n<3 e false otherwise), ne haniboy?
}