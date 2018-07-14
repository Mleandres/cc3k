#ifndef __TREASURE_H__
#define __TREASURE_H__

#include "item.h"

class Treasure : public Item {

	bool dragonSlain;

protected:
	void setSlain(bool s);

public:
	Treasure(Posn p, int amount, std::string type);
	void use(Subject &p) override;

	SubscriptionType getSubType() const override;

	bool canPickUp();
	void pickAction(Subject &p);
	void notify(Subject *whoNotified) override;
};

#endif
