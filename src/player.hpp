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
    void incrementTurns();
    size_type note();
    std::string decision();
    bool operator==( const Player &other ) const {
      if (this->action == other.action && this->m_is_playing == other.m_is_playing && this->m_brain_round == other.m_brain_round && this->m_run_round == other.m_run_round && this->m_shots_round == other.m_shots_round && this->name == other.name){return true;}
      return false;
    };

  //GET METHODS
    const std::string& getName() const;
    size_type getBrains() const;
    size_type getShotguns() const;
    size_type getFootprints() const;
    size_type get_total_brains() const;
    size_type get_turns_played() const;
    size_type get_turn()const;

  //SET METHODS
  void set_name(std::string str){ name = str; }
  void set_decision(std::string act) { action = act; }
  void set_turn(size_type turn){ turn = turn; }
  void set_brain(size_type i){ m_brain_round = i; }
  void set_footprint(size_type i) { m_run_round = i; }
  void set_shotgun(size_type i) {m_shots_round = i;}
  void set_total_brains(size_type i) {m_total_brains = i; }
  void set_turns_played(size_type i) { m_turns_played = i; }
  
private:
  //ATTRIBUTES
    std::string name; 
    bool m_is_playing; ///check if the player is still playing the game
    std::string action;
    size_type m_brain_round;  ///total brains in the round
    size_type m_run_round;    ///total runs in the round
    size_type m_shots_round;  ///total shots in the round
    size_type m_total_brains; ///total brains the player got
    size_type m_turns_played; ///total turns the player played
    size_type m_turn;         ///The order the players are going to play
};

#endif