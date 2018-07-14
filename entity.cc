#include "entity.h"
using namespace std;

Entity::Entity(Posn p, char icon)
	: icon{icon}, curPos{p}, lastPos{p} {}

Entity::~Entity(){}

char Entity::getIcon() const {
	return this->icon;
}

Posn Entity::getCurPos() const {
	return this->curPos;
}

Posn Entity::getLastPos() const {
	return this->lastPos;
}

