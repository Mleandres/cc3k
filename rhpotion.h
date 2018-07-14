#ifndef __RHPOTION_H__
#define __RHPOTION_H__
#include "potion.h"

class RHPotion final : public Potion{
	static bool known;

	public:
	  RHPotion(Posn p);
		void use(Player &p) override;

		bool isKnown();

		void notify(Subject *whoNotified) override;
};

#endif
