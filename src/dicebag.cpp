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

void DiceBag::add_to_used_dice(const std::vector<ZDice>& dice_to_add) {
    for (const auto& die : dice_to_add) {
        used_dice.push_back(die); 
    }
}



std::vector<ZDice> DiceBag::sort_dices(size_t num_dice) {
    std::random_device rd;
    gen = std::mt19937(rd());
    std::shuffle(available_dice.begin(), available_dice.end(), gen);
    if (available_dice.size() < num_dice) {
        num_dice = available_dice.size();
        if (num_dice == 0) return {}; // if there are no dice, end this.
    }
    std::vector<ZDice> drawn_dice; // This dices are going back do game-controller
    for (size_t i = 0; i < num_dice; ++i) {
        drawn_dice.push_back(available_dice.front()); 
        available_dice.erase(available_dice.begin()); 
    }
    return drawn_dice; 
}

void DiceBag::restore_bag(){
    for (ZDice& dice : used_dice){
        available_dice.push_back(dice);
    }
    used_dice.clear();
}

void DiceBag::refill_bag() {
    std::vector<ZDice> remaining_used_dice;
    for (ZDice& dice : used_dice) {
        if (dice.get_result() == "b") {
            available_dice.push_back(dice); // Move 'b' dices back to available_dices
        } else {
            remaining_used_dice.push_back(dice); // Keep those that are not 'b'
        }
    }
    used_dice.clear();
    used_dice = remaining_used_dice; // Move those are not 'b' at used_dice
    // Shuffle the dices
    std::random_device rd;
    gen = std::mt19937(rd());
    std::shuffle(available_dice.begin(), available_dice.end(), gen);
    std::cout << "Sacola reabastecida! Dados disponíveis: " << available_dice.size() << std::endl;
}

bool DiceBag::lower_than_3_dices() { return available_dice.size() < 3;}