#include "Player.h"

void Player::TakeDamage(int damage) {
  m_health -= damage;
  damageTaken.Invoke(this, m_health);
}

int Player::GetHealth() const { return m_health; }
std::string Player::GetName() const { return m_name; }