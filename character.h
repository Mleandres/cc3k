#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__

#include "entity.h"
#include <cmath>

struct Posn;
class Tile;

class Character : public Entity {

	const int maxhp;

	int hp;
	int att;
	int def;

protected:

	virtual void moveEffect();
	virtual bool canMove(const Posn &np);

public:

	Character(int maxhp, int hp, int att, int def, Posn p, char icon);

	void detachTiles();

	// accessors:
	int getMaxHp() const;

	int getHp() const;

	int getAtt() const;

	int getDef() const;

	// char move takes a posn instead of a string direction.
  bool move(const Posn &np);

  int calculateDamage(Character *attacker);

  virtual int defaultAttack(Character *c);

	// mutators:
	void setHp(int newHp);

  void setAtt(int newAtt);

  void setDef(int newDef);

  virtual std::string getRace() const = 0;
};

#endif
