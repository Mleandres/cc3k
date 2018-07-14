#ifndef __TROLL_H__
#define __TROLL_H__

#include "player.h"

class Enemy;

class Troll final : public Player {

public:

  Troll(Posn p);

  int attack(Enemy *enemy) override;

  void moveEffect() override;

  ~Troll();
};

#endif
