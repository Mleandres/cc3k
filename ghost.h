#ifndef __GHOST_H__
#define __GHOST_H__

#include "player.h"

class Enemy;
class Human;

class Ghost final : public Player {

public:

  Ghost(Posn p);

  int attack(Enemy *enemy) override;

  int attackedBy(Human *e) override;

  int potMag() const override;

  ~Ghost();
};

#endif


