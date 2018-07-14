#ifndef __ORC_H__
#define __ORC_H__

#include "enemy.h"

class Player;

class Orc final : public Enemy {

public:
  Orc(Posn p);
  ~Orc();

  int attack(Player *player) override;

  std::string getRace() const override;
};

#endif
