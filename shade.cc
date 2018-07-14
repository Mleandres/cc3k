#include "shade.h"

using namespace std;

// (125 HP, 25 Atk, 25 Def)
Shade::Shade(Posn p)
	: Player{125, 125, 25, 25, p, "Shade"} {}

int Shade::attack(Enemy *enemy) {
  int dmg = enemy->attackedBy(this);
  enemy->checkEnemyDead(this);
  return dmg;
}

Shade::~Shade() {}
