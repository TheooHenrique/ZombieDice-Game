#ifndef DICE_BAG_HPP
#define DICE_BAG_HPP

#include <vector>
#include <string>
#include <cstddef>
#include "zdice.hpp"

class ZDice_Bag {
using size_type = std::size_t;
public:
  size_type m_green_amount;
  size_type m_yellow_amount;
  size_type m_red_amount;
  size_type m_total_dices;
  size_type m_current_count_dices;
  
  ZDice_Bag(){ //Default constructor of the class
    size_type m_green_amount = 6;
    size_type m_yellow_amount = 4;
    size_type m_red_amount = 3;
    size_type m_total_dices = 13;
  }
  //METHODS:
  std::string sort_dices(int num_dice = 3);
  size_type lower_than_3_dices();
  size_type refill_bag();

  const std::string& get_green_amount() const { return green_amount; }
  const std::string& get_yellow_amount() const { return yellow_amount; }
  const std::string& get_red_amount() const { return m_red_amount; }

private:
    std::vector<std::string> available_dice;
    std::vector<std::string> used_dice;
};

#endif
