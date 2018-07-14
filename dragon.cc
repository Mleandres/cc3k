#include "dragon.h"
using namespace std;

Dragon::Dragon(Posn p, Treasure* hoard) : Enemy{150, 150, 20, 20, p, 'D'}, hoard{hoard} {}

Dragon::~Dragon() {}

int Dragon::attack(Player *player) {
  return player->attackedBy(this);
}

void Dragon::checkEnemyDead(Player *killer) {
  if(this->getHp() == 0) {
    this->hoard->notify(this);
  }
}

string Dragon::getRace() const {
  return "Dragon";
}

void Dragon::notify(Subject *whoNotified) {
  cerr << "HELLO IS THIS > NO THIS IS DRAGON" << endl;
    this->nearPlayer = true;
}

SubscriptionType Dragon::getSubType() const {
  return SubscriptionType::Dragon;
}
