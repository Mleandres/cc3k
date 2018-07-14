#include "orc.h"
using namespace std;


Orc::Orc(Posn p) : Enemy{180, 180, 30, 25, p, 'O'} {}

Orc::~Orc() {}

int Orc::attack(Player *player) {
  return player->attackedBy(this);
}

string Orc::getRace() const {
  return "Orc";
}

