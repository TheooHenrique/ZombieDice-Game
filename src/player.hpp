/**
 * @file player.hpp
 * @brief Defines the Player class, which represents a player in the Zombie Dice game.
 * @author Haniel Lucas Machado Rocha
 * @author Theo Henrique da Silva Borges
 * @date June 24th, 2025
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

/**
 * @class Player
 * @brief Represents a player and stores their state throughout the game.
 *
 * This class manages the player's name, accumulated points (brains),
 * the state of the current turn (brains, shotguns, footprints), and other
 * information relevant to gameplay.
 */
class Player {
  /// @brief Alias for the size type used in the class.
  using size_type = size_t;

public:
  /**
    * @brief Default constructor.
    * Creates a player with an empty name and zeroed attributes.
    */
  Player();

  /**
    * @brief Constructor that initializes the player with a name.
    * @param name The player's name.
    */
  Player(const std::string& name);
  
    

  //== GAMEPLAY METHODS ==//
    /**
     * @brief Increments the brain counter for the current round.
     */
    void addBrain();

    /**
     * @brief Increments the shotgun counter for the current round.
     */
    void addShotgun();

    /**
     * @brief Increments the footprint counter for the current round.
     */
    void addFootprint();

    /**
     * @brief Increments the total number of turns the player has played.
     */
    void incrementTurns();

    size_type note();

    /**
     * @brief Returns the player's last decision (e.g., "roll", "skip").
     * @return std::string The player's decision.
     */
    std::string decision();

    /**
     * @brief Overload of the equality operator to compare two players.
     * @param other The other Player object to compare against.
     * @return true If all attributes of the players are identical.
     * @return false If at least one attribute is different.
     */
    bool operator==( const Player &other ) const {
      if (this->action == other.action && this->m_is_playing == other.m_is_playing && this->m_brain_round == other.m_brain_round && this->m_run_round == other.m_run_round && this->m_shots_round == other.m_shots_round && this->name == other.name){return true;}
      return false;
    };

  //== GETTERS (ACCESSORS) ==//
    /**
     * @brief Gets the player's name.
     * @return const std::string& A constant reference to the player's name.
     */
    const std::string& getName() const;

    /**
     * @brief Gets the number of brains accumulated in the current round.
     * @return size_type The number of brains from the round.
     */
    size_type getBrains() const;

    /**
     * @brief Gets the number of shotguns received in the current round.
     * @return size_type The number of shotguns from the round.
     */
    size_type getShotguns() const;

    /**
     * @brief Gets the number of footprints rolled in the current round.
     * @return size_type The number of footprints from the round.
     */
    size_type getFootprints() const;

    /**
     * @brief Gets the player's total brain score for the game.
     * @return size_type The total accumulated brains.
     */
    size_type get_total_brains() const;

    /**
     * @brief Gets the total number of turns played by the player.
     * @return size_type The number of turns played.
     */
    size_type get_turns_played() const;


    size_type get_turn()const;

  //== SETTERS (MUTATORS) ==//
    /**
     * @brief Sets the player's name.
     * @param str The new name for the player.
     */
  void set_name(std::string str){ name = str; }

  /**
     * @brief Sets the player's decision for the round.
     * @param act The string representing the action (e.g., "roll").
     */
  void set_decision(std::string act) { action = act; }

  /**
     * @brief Sets the player's turn order.
     * @param turn The turn order number.
     */
  void set_turn(size_type turn){ turn = turn; }
  void set_brain(size_type i){ m_brain_round = i; }
  void set_footprint(size_type i) { m_run_round = i; }
  void set_shotgun(size_type i) {m_shots_round = i;}
  void set_total_brains(size_type i) {m_total_brains = i; }
  void set_turns_played(size_type i) { m_turns_played = i; }
  
private:
  //== ATTRIBUTES ==//
    std::string name;         ///The identifying player name
    bool m_is_playing;        ///Check if the player is still playing the game
    std::string action;       ///Stores the last action chosen by the player (e.g., "roll", "skip")
    size_type m_brain_round;  ///Counter for brains obtained in the current round.
    size_type m_run_round;    ///Counter for footprints obtained in the current round.
    size_type m_shots_round;  ///Counter for shotguns received in the current round.
    size_type m_total_brains; ///total brains the player got
    size_type m_turns_played; ///total turns the player played
    size_type m_turn;         ///The order the players are going to play
};

#endif