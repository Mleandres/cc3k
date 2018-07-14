#include "subject.h"

void Subject::attach(const Posn &p, Observer *o) {
	this->tileObservers[p] = o;
}

void Subject::attach(Observer *o) {
	this->otherObservers.push_back(o);
}

void Subject::notifyObservers(SubscriptionType t) {
	for (auto &i : tileObservers) {
		if (t == i.second->getSubType()) i.second->notify(this);
	}

	for (auto &i : otherObservers) {
		if (t == i->getSubType()) i->notify(this);
	}

}

/*
void Subject::notifyDisplay() {
	this->display->notifyComing(this);
}
*/
Stats Subject::getStats() const {
	Stats ret{-1,0,0,0,0,"",""};
	return ret;
}

void Subject::setAction(const std::string &s) {
	return;
}

void Subject::appendAction(const std::string &s) {
	return;
}

Subject::~Subject(){}

void Subject::use(Subject &p) {
	return;
}

int Subject::getGold() const {
	return 0;
}

void Subject::pickUpGold(int newGold) {
	return;
}
