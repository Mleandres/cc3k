#include "ghost.h"

using namespace std;

Ghost::Ghost(Posn p)
  : Player{160, 160, 5, 5, p, "Ghost"} {}

int Ghost::attack(Enemy *enemy) {
  int dmg = enemy->attackedBy(this);
  enemy->checkEnemyDead(this);
  return dmg;
}

int Ghost::attackedBy(Human *e) {
  return 0;
}

int Ghost::potMag() const {
  return 5.0;
}

Ghost::~Ghost() {}


