
#ifndef __POTION_H__
#define __POTION_H__

#include <iostream>

#include "item.h"
#include "player.h"

class Potion : public Item {

public:

	Potion(Posn p, int amount, std::string type);
	~Potion();

	SubscriptionType getSubType() const override;

	void useAction(Player &p);

	void encounterAction(Subject &p, bool known);

};

#endif
