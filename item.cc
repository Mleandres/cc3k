#include "item.h"
using namespace std;

// Ctor
Item::Item(Posn p, char c, int amount, string type)
	: Entity{p, c}, amount{amount}, type{type} {}

void Item::notify(Subject *whoNotified) {
	return;
}

char Item::getType() const {
	return this->getIcon();
}

// void Item::notifyComing(Subject *whoNotified){}

// void Item::notifyLeave(){}

/*
SubscriptionType Item::getSubType() const {
	return SubscriptionType::Item;
}
*/
