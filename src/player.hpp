
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {
  using size_type = size_t;
public:
  //Constructor:
  Player(); //DEPOIS TEM QUE FAZER O GAMECONTROLLER RECEBER OS PLAYERS QUE O USUARIO COLOCAR NA LISTA, NÃO ESSE CONSTRUTOR PADRÃO (ta aqui so por gambiarra)
  Player(const std::string& name);
  
    
  //METHODS
    void addBrain();
    void addShotgun();
    void addFootprint();
    size_type note();
    bool decision();

  //GET METHODS
    const std::string& getName() const;
    size_type getBrains() const;
    size_type getShotguns() const;
    size_type getFootprints() const;
    size_type get_total_brains() const;

  //SET METHODS
  void set_name(std::string str){ name = str; };
  
private:
  //ATTRIBUTES
    std::string name;
    bool m_is_playing;
    size_type m_brain_round;
    size_type m_run_round;
    size_type m_shots_round;
    size_type m_total_brains;

};

#endif
