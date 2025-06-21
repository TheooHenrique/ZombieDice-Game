#include "player.hpp"

Player::Player(const std::string& name) : name(name), m_brain_round(0), m_run_round(0), m_shots_round(0) {}

const std::string& Player::getName() const {
    return name;
}

int Player::getBrains() const {
    return m_brain_round;
}

void Player::addBrain() {
    m_brain_round++;
}

void Player::addShotgun() {
    m_shots_round++;
}

void Player::addFootprint() {
    m_run_round++;
}

int Player::getShotguns() const {
    return m_shots_round;
}

int Player::getFootprints() const {
    return m_run_round;
}