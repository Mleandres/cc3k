#include "drow.h"

using namespace std;

Drow::Drow(Posn p)
  : Player{150, 150, 25, 15, p, "Drow"} {}

int Drow::attack(Enemy *enemy) {
  int dmg = enemy->attackedBy(this);
  enemy->checkEnemyDead(this);
  return dmg;
}

int Drow::attackedBy(Elf *e) {
  return this->defaultAttack(e);
}

int Drow::potMag() const {
  return 1.5;
}

Drow::~Drow() {}
