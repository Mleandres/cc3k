#include "phpotion.h"
using namespace std;

bool PHPotion::known = false;

// Ctor
PHPotion::PHPotion(Posn p): Potion{p, 10, "PH"} {}

// use PH potion
void PHPotion::use(Player &p){
	p.setHp(p.getHp() - this->amount * p.potMag());
	this->known = true;
	this->useAction(p);
}

// Checks if potion encountered is known by PC
bool PHPotion::isKnown() {
	return this->known;
}

// updates Action when potion is within 1-block radius of PC
void PHPotion::notify(Subject *whoNotified) {
	this->encounterAction(*whoNotified, this->known);
}

