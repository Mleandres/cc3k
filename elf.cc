#include "elf.h"
using namespace std;


Elf::Elf(Posn p) : Enemy{110, 110, 15, 20, p, 'E'} {}

Elf::~Elf() {}

int Elf::attack(Player *player) {
  return player->attackedBy(this);
}

string Elf::getRace() const {
  return "Elf";
}

