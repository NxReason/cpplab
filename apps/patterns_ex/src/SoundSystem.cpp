#include "SoundSystem.h"

#include <iostream>

void SoundSystem::PlayDamageSound() {
  std::cout << "Play damage sound\n";
}

void SoundSystem::OnPlayerDamageTaken(EventDetails<Player*, int>) {
  PlayDamageSound();
}