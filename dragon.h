#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "enemy.h"
#include "treasure.h"

class Player;
class Treasure;

class Dragon final : public Enemy {
Treasure *hoard;
public:
  Dragon(Posn p, Treasure* hoard);
  ~Dragon();

  int attack(Player *player) override;

  void checkEnemyDead(Player *killer) override;

  std::string getRace() const override;

  SubscriptionType getSubType() const override;

  void notify(Subject *whoNotified) override;
};

#endif
