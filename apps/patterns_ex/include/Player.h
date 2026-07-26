#pragma once

#include <string>
#include "Event.h"

class Player {
public:
  Event<Player*, int> damageTaken {};

  void TakeDamage(int damage);

  int GetHealth() const;
  std::string GetName() const;
private:
  int m_health = 100;
  std::string m_name { "Player 1" };
};