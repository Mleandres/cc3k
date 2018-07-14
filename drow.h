#ifndef __DROW_H__
#define __DROW_H__

#include "player.h"

class Enemy;
class Elf;

class Drow final : public Player {

public:

  Drow(Posn p);

  int attack(Enemy *enemy) override;

  int attackedBy(Elf *e) override;

  int potMag() const override;

  ~Drow();
};

#endif
