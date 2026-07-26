#pragma once

#include <iostream>
#include <string>

#include "Event.h"
#include "Player.h"
#include "Bar.h"
#include "SoundSystem.h"

void showEventExample() {
  Player player;

  // Bar hp{ "Health" };
  auto hp = std::make_shared<Bar>("Health");
  std::weak_ptr<Bar> weakHp = hp;
  Bar mp { "Mana" };
  SoundSystem ss;

  auto hpSub = player.damageTaken.Sub(
    [&weakHp](Player* sender, int health) {
      if (auto hp = weakHp.lock()) {
        hp->OnPlayerDamageTaken({ sender, health });
      }
    }
  );
  auto mpSub = player.damageTaken.Sub(
    [&mp](Player* sender, int health) {
      mp.OnPlayerDamageTaken({ sender, health });
    }
  );
  auto ssSub = player.damageTaken.Sub(
    [&ss](Player* sender, int health) {
      ss.OnPlayerDamageTaken({ sender, health });
    }
  );

  std::cout << "--- First hit ---\n";
  player.TakeDamage(25);

  mpSub.Reset();
  std::cout << "--- Second hit ---\n";
  player.TakeDamage(10);

  ssSub.Reset();
  std::cout << "--- Third hit ---\n";
  player.TakeDamage(10);
}