#ifndef DICE_BAG_HPP
#define DICE_BAG_HPP

#include <vector>
#include <string>
#include <cstddef>

class DiceBag {
using size_type = std::size_t;
public:
  size_type m_green_amount;
  size_type m_yellow_amount;
  size_type m_red_amount;
  size_type m_total_dices;
  size_type m_current_count_dices;
  
  DiceBag(){ //Default constructor of the class
    size_type m_green_amount = 6;
    size_type m_yellow_amount = 4;
    size_type m_red_amount = 3;
    size_type m_total_dices = 13;
  }
  DiceBag(size_type green, size_type yellow, size_type red, size_type total);

  //METHODS:
  std::string sort_dices(int num_dice = 3);
  size_type lower_than_3_dices();
  size_type refill_bag();

  const size_type& get_green_amount() const { return m_green_amount; }
  const size_type& get_yellow_amount() const { return m_yellow_amount; }
  const size_type& get_red_amount() const { return m_red_amount; }

private:
    std::vector<std::string> available_dice;
    std::vector<std::string> used_dice;
};

#endif
