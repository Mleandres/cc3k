#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "character.h"
#include "player.h"


class Shade;
class Drow;
class Vampire;
class Goblin;
class Troll;
class Ghost;

class Subject;

class Enemy : public Character, public Observer {

protected:
	bool nearPlayer;

public:

	Enemy(int maxhp, int hp, int att, int def, Posn p, char icon);

	SubscriptionType getSubType() const override;

	void notify(Subject *whoNotified) override;

	char getType() const override;

  bool isNearPlayer() const;

  void setNearPlayer(bool b);

  virtual bool isHostile() const;

	virtual ~Enemy() = default;

  virtual void checkEnemyDead(Player *killer);

  virtual int attack(Player *player) = 0;

  virtual int attackedBy(Shade *e);

  virtual int attackedBy(Drow *e);

  virtual int attackedBy(Goblin *e);

  virtual int attackedBy(Vampire *e);

  virtual int attackedBy(Troll *e);

  virtual int attackedBy(Ghost *e);

};

#include "elf.h"
#include "merchant.h"
#include "halfling.h"
#include "dragon.h"
#include "human.h"
#include "dwarf.h"
#include "orc.h"
#endif
