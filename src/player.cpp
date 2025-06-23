#include "player.hpp"

using size_type = size_t;

Player::Player() : name(""), m_brain_round(0), m_run_round(0), m_shots_round(0), m_total_brains(0), m_is_playing(false) {}

Player::Player(const std::string& name) : name(name), m_brain_round(0), m_run_round(0), m_shots_round(0) {}

const std::string& Player::getName() const { return name; }
size_type Player::getBrains() const { return m_brain_round; }
size_type Player::getShotguns() const { return m_shots_round; }
size_type Player::getFootprints() const { return m_run_round; }
size_type Player::get_total_brains() const { return m_total_brains; }
void Player::addBrain() { m_brain_round++; }
void Player::addShotgun() { m_shots_round++; }
void Player::addFootprint() { m_run_round++; }
bool Player::decision() {
    // Lógica temporária: por enquanto, o jogador sempre decide continuar.
    // TODO: Implementar a lógica real de decisão do jogador.
    return true;
}