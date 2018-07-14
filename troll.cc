#include "troll.h"

using namespace std;

Troll::Troll(Posn p)
  : Player{120, 120, 25, 15, p, "Troll"} {}

int Troll::attack(Enemy *enemy) {
  int dmg = enemy->attackedBy(this);
  enemy->checkEnemyDead(this);
  return dmg;
}

Troll::~Troll() {}

void Troll::moveEffect() {
	this->setHp(this->getHp() + 5);
}
