
#include <cstdlib>
#include <ctime>

#include "goblin.h"

using namespace std;

// goblin (110 HP, 15 Atk, 20 Def, steals 5 gold from every slain enemy)
Goblin::Goblin(Posn p) : Player{110, 110, 15, 20, p, "Goblin"} {}

int Goblin::attack(Enemy *enemy) {
  int dmg = enemy->attackedBy(this);
  enemy->checkEnemyDead(this);
  if(enemy->getHp() == 0) {
    Treasure t{this->getCurPos(), 5, "gobDrop"};
    t.use(*this);
  }
  return dmg;
}

int Goblin::attackedBy(Orc *e) {
  double dmg = double(this->calculateDamage(e));
  dmg *= 1.5;
  this->setHp(this->getHp() - dmg);
  return dmg;
}

Goblin::~Goblin() {}


