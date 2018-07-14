#ifndef __SHADE_H__
#define __SHADE_H__

#include "player.h"

class Enemy;

class Shade final : public Player {

public:

	Shade(Posn p);

  int attack(Enemy *enemy) override;

  ~Shade();
};



#endif
