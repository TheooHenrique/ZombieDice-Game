#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

class Player {
public:
    Player(const std::string& name);

    const std::string& getName() const;
    int getBrains() const;
    void addBrain();
    void addShotgun();
    void addFootprint();
    int getShotguns() const;
    int getFootprints() const;

private:
    std::string name;
    int brains;
    int shotguns;
    int footprints;
};

#endif