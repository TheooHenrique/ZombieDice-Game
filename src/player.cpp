#include "player.hpp"

Player::Player(const std::string& name) : name(name), brains(0), shotguns(0), footprints(0) {}

const std::string& Player::getName() const {
    return name;
}

int Player::getBrains() const {
    return brains;
}

void Player::addBrain() {
    brains++;
}

void Player::addShotgun() {
    shotguns++;
}

void Player::addFootprint() {
    footprints++;
}

int Player::getShotguns() const {
    return shotguns;
}

int Player::getFootprints() const {
    return footprints;
}