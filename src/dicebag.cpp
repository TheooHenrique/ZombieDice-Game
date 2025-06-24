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

std::string DiceBag::sort_dices(size_t num_dice) {
    if (available_dice.size() < get_dices_amount()) { 
        std::cout << "QUASE ENTREI EM REFILL_BAG";
        refill_bag(); }
    std::random_device rd;
    gen = std::mt19937(rd());
    std::shuffle(available_dice.begin(), available_dice.end(), gen);

    std::string result;
    for (size_t i{0}; i < num_dice ; ++i) {
        if (available_dice[i].get_green()){ result += "g"; }
        else if (available_dice[i].get_yellow()){ result += "y"; }
        else if (available_dice[i].get_red()){ result += "r"; }
        used_dice.push_back(available_dice.front());
        available_dice.erase(available_dice.begin() + i);
        
    }
    return result;
}

void DiceBag::refill_bag() {
    ///Restore the DiceBag with all dices that result in brain.
    std::cout << "ENTREI EM REFILL_BAG!!!!\n\n\n";
    for (size_type i{0}; i < used_dice.size(); ++i){
        if(used_dice[i].get_result() == "b"){
            available_dice.push_back(used_dice[i]);
        }
    }
}

bool DiceBag::lower_than_3_dices() { return available_dice.size() < 3;}