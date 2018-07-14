#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "subject.h"

// Entity is an abstract class
class Entity : public Subject {

	char icon;

protected:
	Posn curPos;
	Posn lastPos;

public:

	Entity(Posn p, char icon);

  Posn getCurPos() const override;
  Posn getLastPos() const override;
  char getIcon() const override;
  //virtual void use(Player &p);
  virtual ~Entity() = 0;
};

#endif
