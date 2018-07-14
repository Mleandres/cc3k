#ifndef __DWARF_H__
#define __DWARF_H__

#include "enemy.h"

class Player;

class Dwarf final : public Enemy {

public:
  Dwarf(Posn p);
  ~Dwarf();

  int attack(Player *player) override;

  int attackedBy(Vampire *e) override;

  std::string getRace() const override;
};

#endif
