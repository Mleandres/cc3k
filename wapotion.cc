#include "wapotion.h"
using namespace std;

bool WAPotion::known = false;

// Ctor
WAPotion::WAPotion(Posn p): Potion{p, 5, "WA"} {}

// use WA potion
void WAPotion::use(Player &p){
	p.setAtt(p.getAtt() - this->amount * p.potMag());
	this->known = true;
	this->useAction(p);
}

// Checks if potion encountered is known by PC
bool WAPotion::isKnown() {
	return this->known;
}

// updates Action when potion is within 1-block radius of PC
void WAPotion::notify(Subject *whoNotified) {
	this->encounterAction(*whoNotified, this->known);
}

