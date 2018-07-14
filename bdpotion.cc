#include "bdpotion.h"
using namespace std;

bool BDPotion::known = false;

// Ctor
BDPotion::BDPotion(Posn p): Potion{p, 5, "BD"} {}

// use BD potion
void BDPotion::use(Player &p){
	p.setDef(p.getDef() + this->amount * p.potMag());
	this->known = true;
	this->useAction(p);
}

// Checks if potion encountered is known by PC
bool BDPotion::isKnown() {
	return this->known;
}

// updates Action when potion is within 1-block radius of PC
void BDPotion::notify(Subject *whoNotified) {
	this->encounterAction(*whoNotified, this->known);
}
