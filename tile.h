#ifndef __TILE_H__
#define __TILE_H__

#include "subject.h"
#include "observer.h"
#include "posn.h"
#include "entity.h"

class Subject;
struct Posn;

class Tile final : public Subject, public Observer {
  Entity *e;
	Posn p;
  const char base;
	char type; // used for printing to display and determining its type
	int chamber; // which chamber is it in

public:

// constructor
	Tile(Posn p, char type);

// accessors
  Posn getPosn() const;
  char getType() const override;
  int getChamber() const;

// observer methods
  //notifies this tile that the thing previously on it has left (and thus revert to default)
  void notifyLeave();

  void notify(Subject *whoNotified) override;
  //void notifyComing(char c);

  SubscriptionType getSubType() const override;

// subject methods
  Posn getCurPos() const override;
  Posn getLastPos() const override;
  char getIcon() const override;

// mutators
  void setChamber(int cham);

  ~Tile();
};

#endif
