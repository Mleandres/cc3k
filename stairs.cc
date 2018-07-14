#include "stairs.h"

using namespace std;

Stairs::Stairs(Posn p) : Entity{p, 92} {}

Stairs::~Stairs() {}

void Stairs::notify(Subject *whoNotified) {}

char Stairs::getType() const {
	return this->getIcon();
}

SubscriptionType Stairs::getSubType() const {
	return SubscriptionType::Stairs;
}
