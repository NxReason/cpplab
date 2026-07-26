#pragma once

#include "Event.h"
#include "Player.h"

class SoundSystem {
public:
  void PlayDamageSound();

  void OnPlayerDamageTaken(EventDetails<Player*, int>);
};
