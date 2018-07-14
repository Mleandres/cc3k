#include "potion.h"
using namespace std;

// Ctor
Potion::Potion(Posn p, int amount, string type): Item{p, 'P', amount, type} {}

// Dtor
Potion::~Potion() {}

SubscriptionType Potion::getSubType() const {
	return SubscriptionType::Potion;
}

// updates Action of Player after using potion
void Potion::useAction(Player &p) {
	Stats s = p.getStats();
	p.appendAction(s.race + " uses " + this->type);
}

// updates Action when PC encounters potion
void Potion::encounterAction(Subject &p, bool known) {
	Stats s = p.getStats();
	if (known) {
		p.appendAction("sees a " + this->type + " potion");
	}
	else {
		p.appendAction("sees an unknown potion");
	}
}
