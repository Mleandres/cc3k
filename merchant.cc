#include "merchant.h"
using namespace std;

bool Merchant::hostile = false;

Merchant::Merchant(Posn p) : Enemy{30, 30, 70, 5, p, 'M'}{}

Merchant::~Merchant() {}

int Merchant::attack(Player *player) {
  return player->attackedBy(this);
}

bool Merchant::isHostile() const {
  return this->hostile;
}

string Merchant::getRace() const {
  return "Merchant";
}

void Merchant::checkEnemyDead(Player *killer) {
  if(this->getHp() == 0) {
  	int addedGold = 4;
    Treasure t{killer->getCurPos(), addedGold, "drop"};
    t.use(*killer);
  }
}


int Merchant::defaultAttack(Character *c) {
  int dmg = this->calculateDamage(c);
  this->setHp(this->getHp() - dmg);
  Merchant::hostile = true;
  return dmg;
}

void Merchant::noHostile() {
	Merchant::hostile = false;
}
