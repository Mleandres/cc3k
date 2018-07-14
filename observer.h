#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "subscriptions.h"
class Subject;
class Player;

class Observer {
public:
	/*
	virtual void notifyComing(Subject *whoNotified) = 0;
	virtual void notifyLeave() = 0 ;
	*/
	virtual void notify(Subject *whoNotified) = 0;
	virtual char getType() const = 0;
	virtual void use(Player &p);
	virtual SubscriptionType getSubType() const = 0;
	virtual ~Observer() = default;

};

#endif
