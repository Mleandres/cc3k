#ifndef __HALFLING_H__
#define __HALFLING_H__

#include "enemy.h"
#include <cstdlib>

class Player;

class Halfling final : public Enemy {

public:
  Halfling(Posn p);
  ~Halfling();

  int attack(Player *player) override;

  int defaultAttack(Character *c) override;

  std::string getRace() const override;
};

#endif
