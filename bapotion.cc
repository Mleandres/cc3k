#include "bapotion.h"

using namespace std;

bool BAPotion::known = false;

// Ctor
BAPotion::BAPotion(Posn p): Potion{p, 5, "BA"} {}

// use BA potion
void BAPotion::use(Player &p) {
	p.setAtt(p.getAtt() + this->amount * p.potMag());
	this->known = true;
	this->useAction(p);
}

// Checks if potion encountered is known by PC
bool BAPotion::isKnown() {
	return this->known;
}

// updates Action when potion is within 1-block radius of PC
void BAPotion::notify(Subject *whoNotified) {
	this->encounterAction(*whoNotified, this->known);
}
