#ifndef DICE_BAG_HPP
#define DICE_BAG_HPP

#include <random>
#include <vector>
#include <string>
#include <cstddef>
#include "zdice.hpp"

class DiceBag {
using size_type = std::size_t;
public:
  //Default constructor of the class
  DiceBag();
  //Constructor receiving the amount of each dice from initializer
  DiceBag(size_type green_amount, size_type yellow_amount, size_type red_amount, std::string green_faces, std::string yellow_faces, std::string red_faces);

  //METHODS:
  std::vector<ZDice> sort_dices(size_t num_dice = 3);
  bool lower_than_3_dices();
  void refill_bag();
  void restore_bag();
  void add_to_used_dice(const std::vector<ZDice>& dice_to_add);

  //GET METHODS
  size_t get_available_dice_count() const { return available_dice.size(); }
  const size_type& get_green_amount() const { return m_green_amount; }
  const size_type& get_yellow_amount() const { return m_yellow_amount; }
  const size_type& get_red_amount() const { return m_red_amount; }
  const size_type get_dices_amount() const { return available_dice.size(); }
  const size_type& get_current_count() const {return m_current_count_dices; }
  std::vector<ZDice>& get_available_dice() {return available_dice; }
  std::vector<ZDice>& get_used_dice() {return used_dice; }
  

  //SET METHODS 
  void set_available_dice(ZDice value){ available_dice.push_back(value); }
  void set_used_dice(ZDice d){ used_dice.push_back(d); }

private:
    size_type m_green_amount;
    size_type m_yellow_amount;
    size_type m_red_amount;
    size_type m_total_dices;
    size_type m_current_count_dices;
    std::vector<ZDice> available_dice;
    std::vector<ZDice> used_dice;
    mutable std::mt19937 gen;
};

#endif
