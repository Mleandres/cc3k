#include "rhpotion.h"
using namespace std;

bool RHPotion::known = false;

// Ctor
RHPotion::RHPotion(Posn p): Potion{p, 10, "RH"} {}

// use RH potion
void RHPotion::use(Player &p){
	p.setHp(p.getHp() + this->amount * p.potMag());
	this->known = true;
	this->useAction(p);
}

// Checks if potion encountered is known by PC
bool RHPotion::isKnown() {
	return this->known;
}

// updates Action when potion is within 1-block radius of PC
void RHPotion::notify(Subject *whoNotified) {
	this->encounterAction(*whoNotified, this->known);
}

