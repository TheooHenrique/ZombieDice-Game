#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {
  using size_type = size_t;
public:
  //Constructor:
  Player();
  Player(const std::string& name);
  
    
  //METHODS
    void addBrain();
    void addShotgun();
    void addFootprint();
    void incrementTurns();
    size_type note();
    bool decision();

  //GET METHODS
    const std::string& getName() const;
    size_type getBrains() const;
    size_type getShotguns() const;
    size_type getFootprints() const;
    size_type get_total_brains() const;
    size_type get_turns_played() const;

  //SET METHODS
  void set_name(std::string str){ name = str; }
  void set_decision(bool act) { action = act; }
  
private:
  //ATTRIBUTES
    std::string name; 
    bool m_is_playing; ///check if the player is still playing the game
    bool action;
    size_type m_brain_round;  ///total brains in the round
    size_type m_run_round;    ///total runs in the round
    size_type m_shots_round;  ///total shots in the round
    size_type m_total_brains; ///total brains the player got
    size_type m_turns_played; ///total turns the player played

};

#endif
