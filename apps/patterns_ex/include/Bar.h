#pragma once

#include <string>
#include "Player.h"
#include "Event.h"

class Bar {
public:
  Bar();
  Bar(const std::string& name);

  void Update(int value);

  void OnPlayerDamageTaken(EventDetails<Player*, int> details);
private:
  std::string m_name;
};