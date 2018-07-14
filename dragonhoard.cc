#include "dragonhoard.h"
using namespace std;

// Ctor
DragonHoard::DragonHoard(Posn p): Treasure{p, 6, "dHoard"} {
	this->setSlain(false);
}
// Notify
void DragonHoard::notify(Subject *whoNotified){
	// Case 1: Subject is Dragon
	if (whoNotified->getIcon() == 'D') {
		this->setSlain(true);
	}
	// Case 2: Subject is PC
	else {
    if(this->canPickUp() && whoNotified->getCurPos() == this->getCurPos()) {
		  this->use(*whoNotified);
    } else {
      this->notifyObservers(SubscriptionType::Dragon);
      Stats s = whoNotified->getStats();
      if (whoNotified->getCurPos() == this->getCurPos()) {
				whoNotified->appendAction("cannot pick up gold because the dragon has not been slain");
			}
    }
	}
}
