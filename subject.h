#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>
#include <map>

#include "posn.h"
#include "subscriptions.h"
#include "observer.h"
#include "stats.h"

struct Posn;
struct Stats;
class Display;

class Subject {

protected:
	std::vector<Observer *> otherObservers;
	std::map<Posn, Observer *> tileObservers;

public:
	void attach(const Posn &p, Observer *o);
	void attach(Observer *o);

	void notifyObservers(SubscriptionType t);

  virtual Posn getCurPos() const = 0;
  virtual Posn getLastPos() const = 0;
  virtual char getIcon() const = 0;
  virtual void setAction(const std::string &s);
  virtual void appendAction(const std::string &s);
	virtual void use(Subject &p);
  virtual Stats getStats() const;
	virtual int getGold() const;
	virtual void pickUpGold(int newGold);
	virtual ~Subject() = 0;
};

#endif
