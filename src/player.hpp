
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {
  using size_type = size_t;
public:
  //Constructor:
  Player(); //DEPOIS TEM QUE FAZER O GAMECONTROLLER RECEBER OS PLAYERS QUE O USUARIO COLOCAR NA LISTA, NÃO ESSE CONSTRUTOR PADRÃO
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
  size_type m_brain_round;
  size_type m_run_round;
  size_type m_shots_round;
  size_type m_total_brains;

private:
//PRIVATE ATTRIBUTES
    std::string name;

};

#endif
