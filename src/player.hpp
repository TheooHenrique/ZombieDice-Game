
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

class Player {
  using size_type = size_t;
public:
    Player(const std::string& name);
  //METHODS
    void addBrain();
    void addShotgun();
    void addFootprint();
    size_type note();
    bool decision();

  //GET METHODS
    const std::string& getName() const;
    int getBrains() const;
    int getShotguns() const;
    int getFootprints() const;
  
  //ATTRIBUTES:
  bool m_is_playing;

private:
  
    std::string name;
    size_type m_brain_round;
    size_type m_run_round;
    size_type m_shots_round;
    size_type m_total_brains;
};

#endif
