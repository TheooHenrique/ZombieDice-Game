/**
 * @file zdice.hpp
 * @brief Defines the ZDice class, which represents a single die in the game.
 * @author Haniel Lucas Machado Rocha
 * @author Theo Henrique da Silva Borges
 * @date June 24, 2025
 */

#ifndef ZDICE_HPP
#define ZDICE_HPP

#include <random>
#include <string>

/**
 * @class ZDice
 * @brief Represents a single Zombie Dice die.
 *
 * This class manages the die's color, its faces (brain, shotgun, footprint),
 * and the logic for rolling it to get a random result.
 */
class ZDice{
    /// @brief Alias for the size type used in the class.
    using size_type = size_t;

public:
    /**
     * @brief Constructs a ZDice object.
     * @param green A boolean flag, true if the die is green.
     * @param yellow A boolean flag, true if the die is yellow.
     * @param red A boolean flag, true if the die is red.
     * @param faces A string representing all faces of the die (e.g., "bbffs").
     */
    ZDice(bool green, bool yellow, bool red, std::string faces);

    /**
     * @brief Simulates a roll of the die.
     * It shuffles the faces and returns one at random.
     * @return std::string A single character string representing the result ('b', 's', or 'f').
     */
    std::string roll();

    //== GETTERS (ACCESSORS) ==//
    /**
     * @brief Gets the string representing all the die's faces.
     * @return const std::string The faces of the die.
     */
    const std::string get_faces() const { return faces; }

    /**
     * @brief Gets the result of the last roll.
     * @return const std::string The last result ('b', 's', or 'f').
     */
    const std::string get_result() const { return roll_result; }

    /**
     * @brief Checks if the die is green.
     * @return const bool True if the die is green, false otherwise.
     */
    const bool get_green() const { return m_green; }

    /**
     * @brief Checks if the die is yellow.
     * @return const bool True if the die is yellow, false otherwise.
     */
    const bool get_yellow() const { return m_yellow; }

    /**
     * @brief Checks if the die is red.
     * @return const bool True if the die is red, false otherwise.
     */
    const bool get_red() const { return m_red; }

    //== SETTERS (MUTATORS) ==//
    /**
     * @brief Sets or updates the faces of the die.
     * @param f The new string of faces.
     */
    void set_faces(std::string f){ faces = f; }

    private:
    //== ATTRIBUTES ==//
    bool m_green;             /// True if this is a green die.
    bool m_yellow;            /// True if this is a yellow die. The 'true' flag determines the die's type and its face values.
    bool m_red;               /// True if this is a red die.
    std::string faces;        /// A string containing all faces, e.g., "bbbffs".
    std::string roll_result;  /// Stores the result of the most recent roll.
    mutable std::mt19937 gen; /// The random number generator for this die. `mutable` allows it to be modified even in const methods.
};

#endif