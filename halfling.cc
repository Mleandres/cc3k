#include "halfling.h"
using namespace std;


Halfling::Halfling(Posn p) : Enemy{100, 100, 15, 20, p, 'L'} {}

Halfling::~Halfling() {}

int Halfling::attack(Player *player) {
  return player->attackedBy(this);
}

int Halfling::defaultAttack(Character *c) {
    if (rand() % 2 == 1) {
      return 0;
    }
    int dmgDealt = this->calculateDamage(c);
    this->setHp(this->getHp() - dmgDealt);
    return dmgDealt;
  }

string Halfling::getRace() const {
  return "Halfling";
}

