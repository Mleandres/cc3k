#include "tile.h"

using namespace std;

Tile::Tile(Posn p, char type) : p{p}, base{type}, type{type}, chamber{0} {

}

char Tile::getType() const {
  return this->type;

}

void Tile::notifyLeave() {
    this->type = '.'; // sets cell to empty
}


void Tile::notify(Subject *whoNotified) {
    this->type = whoNotified->getIcon();
    this->notifyObservers(SubscriptionType::Display);
}
/*
void Tile::notifyComing(char c) {
  this->type = c;
  this->notifyDisplay();
}
*/

SubscriptionType Tile::getSubType() const {
	return SubscriptionType::Move;
}

Posn Tile::getCurPos() const {
  return this->p;
}

Posn Tile::getLastPos() const {
  return this->p;
}

char Tile::getIcon() const {
  return this->type;
}

int Tile::getChamber() const {
	return chamber;

}

void Tile::setChamber(int cham) {
	chamber = cham;
}

Posn Tile::getPosn() const {
	return p;
}

Tile::~Tile(){}
