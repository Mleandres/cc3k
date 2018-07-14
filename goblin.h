#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include "player.h"

class Enemy;

class Goblin final : public Player {

public:

	Goblin(Posn p);

  int attack(Enemy *enemy) override;

  int attackedBy(Orc *e) override;

  ~Goblin();

};

#endif
