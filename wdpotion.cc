#include "wdpotion.h"
using namespace std;

bool WDPotion::known = false;

// Ctor
WDPotion::WDPotion(Posn p): Potion{p, 5, "WD"} {}

// use WD potion
void WDPotion::use(Player &p){
	p.setDef(p.getDef() - this->amount * p.potMag());
	this->known = true;
	this->useAction(p);
}

// Checks if potion encountered is known by PC
bool WDPotion::isKnown() {
	return this->known;
}

// updates Action when potion is within 1-block radius of PC
void WDPotion::notify(Subject *whoNotified) {
	this->encounterAction(*whoNotified, this->known);
}

