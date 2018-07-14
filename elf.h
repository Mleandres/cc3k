#ifndef __ELF_H__
#define __ELF_H__

#include "enemy.h"

class Player;

class Elf final : public Enemy {

public:
  Elf(Posn p);
  ~Elf();

  int attack(Player *player) override;

  std::string getRace() const override;
};

#endif
