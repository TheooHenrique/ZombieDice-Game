#include "dicebag.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include "zdice.hpp"
using size_type = size_t;

//Default constructor
  DiceBag::DiceBag() : m_green_amount(6), m_yellow_amount(4), m_red_amount(3), m_total_dices(13){ 
    ZDice green_dice(true, false, false, "bbbffs");
    ZDice yellow_dice(false, true, false, "bbffss");
    ZDice red_dice(false, false, true, "bffsss");
    for (int i = 0; i < m_green_amount; ++i) available_dice.push_back(green_dice);
    for (int i = 0; i < m_yellow_amount; ++i) available_dice.push_back(yellow_dice);
    for (int i = 0; i < m_red_amount; ++i) available_dice.push_back(red_dice);
  }

//Constructor Receiving data from initializer
DiceBag::DiceBag(size_type green_amount, size_type yellow_amount, size_type red_amount, std::string green_faces, std::string yellow_faces, std::string red_faces){
    m_green_amount = green_amount;
    m_yellow_amount = yellow_amount;
    m_red_amount = red_amount;
    m_total_dices = m_green_amount + yellow_amount + red_amount;

    ZDice green_dice(true, false, false, green_faces);
    ZDice yellow_dice(false, true, false, yellow_faces);
    ZDice red_dice(false, false, true, red_faces);

    //available_dice.clear();

    for (int i = 0; i < green_amount; ++i) available_dice.push_back(green_dice);
    for (int i = 0; i < yellow_amount; ++i) available_dice.push_back(yellow_dice);
    for (int i = 0; i < red_amount; ++i) available_dice.push_back(red_dice);
}

std::vector<ZDice> DiceBag::sort_dices(size_t num_dice) {
    std::vector<ZDice> sorted_dice;
    std::random_device rd;
    gen = std::mt19937(rd());
    std::shuffle(available_dice.begin(), available_dice.end(), gen);

    size_type number_dice_to_get = std::min(num_dice, available_dice.size());

    for (size_t i = 0; i < number_dice_to_get; ++i) {
        sorted_dice.push_back(available_dice.front());
        used_dice.push_back(available_dice.front());
        available_dice.erase(available_dice.begin());
    }

    return sorted_dice;


}

void DiceBag::refill_bag() {
// Move todos os dados com resultado "brain" de volta para available_dice
    auto it = std::remove_if(used_dice.begin(), used_dice.end(), 
        [this](const ZDice& dice) {
            if (dice.get_result() == "b") {
                available_dice.push_back(dice);
                return true;
            }
            return false;
        });
    
    used_dice.erase(it, used_dice.end());
    
    // Embaralha os dados disponíveis
    std::random_device rd;
    gen = std::mt19937(rd());
    std::shuffle(available_dice.begin(), available_dice.end(), gen);
}

bool DiceBag::lower_than_3_dices() { return available_dice.size() < 3;}