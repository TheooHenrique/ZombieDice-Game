/**
 * @file dicebag.hpp
 * @brief Defines the DiceBag class, which manages the collection of dice for the game.
 * @author Haniel Lucas Machado Rocha
 * @author Theo Henrique da Silva Borges
 * @date June 24th, 2025
 */

#ifndef DICE_BAG_HPP
#define DICE_BAG_HPP

#include <random>
#include <vector>
#include <string>
#include <cstddef>
#include "zdice.hpp"

/**
 * @class DiceBag
 * @brief Represents the bag of dice from which players draw.
 *
 * This class holds all the dice, both available and used. It is responsible for
 * shuffling the dice, allowing players to draw from the bag, and managing the
 * dice quantities.
 */
class DiceBag {
  /// @brief Alias for the size type used in the class.
  using size_type = std::size_t;
public:
   /**
     * @brief Default constructor.
     * Initializes the bag with the standard game setup: 6 green, 4 yellow, and 3 red dice.
     */
  DiceBag();

  /**
     * @brief Constructor that receives dice quantities and faces from an initializer.
     * @param green_amount The number of green dice.
     * @param yellow_amount The number of yellow dice.
     * @param red_amount The number of red dice.
     * @param green_faces A string representing the faces of the green dice.
     * @param yellow_faces A string representing the faces of the yellow dice.
     * @param red_faces A string representing the faces of the red dice.
     */
  DiceBag(size_type green_amount, size_type yellow_amount, size_type red_amount, std::string green_faces, std::string yellow_faces, std::string red_faces);

  //== GAMEPLAY METHODS ==//
    /**
     * @brief Randomly draws a specified number of dice from the bag.
     * This method shuffles the bag, removes dice from the top, and returns them.
     * @param num_dice The number of dice to draw, defaults to 3.
     * @return std::vector<ZDice> A vector containing the dice that were drawn.
     */
  std::vector<ZDice> sort_dices(size_t num_dice = 3);

  /**
     * @brief Checks if there are fewer than 3 dice available in the bag.
     * @return true If the number of available dice is less than 3.
     * @return false Otherwise.
     */
  bool lower_than_3_dices();

  /**
     * @brief Returns dice to the bag according to game rules.
     * Currently moves used dice that resulted in a 'brain' back to the available pile.
     */
  void refill_bag();


  //== GETTERS (ACCESSORS) ==//
  /**
   * @brief Gets the initial number of green dice.
   * @return const size_type& The number of green dice.
   */
  const size_type& get_green_amount() const { return m_green_amount; }

  /**
   * @brief Gets the initial number of yellow dice.
   * @return const size_type& The number of yellow dice.
   */
  const size_type& get_yellow_amount() const { return m_yellow_amount; }

  /**
     * @brief Gets the initial number of red dice.
     * @return const size_type& The number of red dice.
     */
  const size_type& get_red_amount() const { return m_red_amount; }

  /**
     * @brief Gets the current number of dice available in the bag.
     * @return const size_type The current size of the available dice vector.
     */
  const size_type get_dices_amount() const { return available_dice.size(); }

  /**
     * @brief Gets the current count of dice (Unused).
     * @return const size_type& A reference to m_current_count_dices.
     */
  const size_type& get_current_count() const {return m_current_count_dices; }

  /**
     * @brief Gets a reference to the vector of available dice.
     * @return std::vector<ZDice>& A mutable reference to the available dice.
     */
  std::vector<ZDice>& get_available_dice() {return available_dice; }

  /**
     * @brief Gets a reference to the vector of used dice.
     * @return std::vector<ZDice>& A mutable reference to the used dice.
     */
  std::vector<ZDice>& get_used_dice() {return used_dice; }

  //== SETTERS (MUTATORS) ==//
    /**
     * @brief Adds a single die to the bag of available dice.
     * @param value The ZDice object to add.
     */ 
  void set_available_dice(ZDice value){ available_dice.push_back(value); }

private:
    //== ATTRIBUTES ==//
    size_type m_green_amount;           ///< The starting number of green dice.
    size_type m_yellow_amount;          ///< The starting number of yellow dice.
    size_type m_red_amount;             ///< The starting number of red dice.
    size_type m_total_dices;            ///< The total number of dice at the start.
    size_type m_current_count_dices;    ///< A counter for dice (currently unused in logic).
    std::vector<ZDice> available_dice;  ///< The collection of dice currently in the bag, available to be drawn.
    std::vector<ZDice> used_dice;       ///< The collection of dice that have been drawn from the bag.
    mutable std::mt19937 gen;           ///< The random number generator for shuffling.
};

#endif
