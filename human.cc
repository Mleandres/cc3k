#include "human.h"
#include <sstream>
using namespace std;

Human::Human(Posn p) : Enemy{140, 140, 20, 20, p, 'H'} {}

Human::~Human() {}

int Human::attack(Player *player) {
  return player->attackedBy(this);
}

void Human::checkEnemyDead(Player *killer) {
  if(this->getHp() == 0) {
    int addedGold = 4;
   	Treasure t{killer->getCurPos(), addedGold, "humanDrop"};
    t.use(*killer);
  }
}

string Human::getRace() const {
  return "Human";
}

