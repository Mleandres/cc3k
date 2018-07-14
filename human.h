#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "enemy.h"

class Player;

class Human final : public Enemy {

public:
  Human(Posn p);
  ~Human();

  int attack(Player *player) override;

  void checkEnemyDead(Player *killer) override;

  std::string getRace() const override;
};

#endif


