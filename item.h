#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
#include "entity.h"
#include "observer.h"

class Player;

class Item : public Entity, public Observer {

protected:
	int amount;
	std::string type;

public:
	Item(Posn p, char c, int amount, std::string type);
	virtual ~Item() = default;

	/*
	void notifyComing(Subject *whoNotified) override;
	void notifyLeave() override;
	*/
	char getType() const override;
	void notify(Subject *whoNotified) override;
	//SubscriptionType getSubType() const override;

};

#endif
