#ifndef DICE_BAG_HPP
#define DICE_BAG_HPP

#include <vector>
#include <string>
#include "zdice.hpp"

class ZDice_Bag {
public:
    ZDice_Bag(int green = 6, int yellow = 4, int red = 3, const std::string& weak_faces = "bbbffs", const std::string& strong_faces = "bbffss", const std::string& tough_faces = "bffsss");

    std::string sort_dices(int num_dice = 3);
    int verifyNumberDices();
    void refill();

    const std::string& get_weak_faces() const { return weak_faces; }
    const std::string& get_strong_faces() const { return strong_faces; }
    const std::string& get_tough_faces() const { return tough_faces; }

private:
    std::vector<std::string> available_dice;
    std::vector<std::string> used_dice;

    std::string weak_faces;
    std::string strong_faces;
    std::string tough_faces;
};

#endif