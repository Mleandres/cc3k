#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__

#include "player.h"

class Enemy;

class Vampire final : public Player {

public:

  Vampire(Posn p);

  int attack(Enemy *enemy) override;

  ~Vampire();
};

#endif
