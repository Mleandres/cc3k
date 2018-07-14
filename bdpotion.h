#ifndef __BDPOTION_H__
#define __BDPOTION_H__
#include "potion.h"

class BDPotion final : public Potion{
	static bool known;

	public:
	  BDPotion(Posn p);
		void use(Player &p) override;

		bool isKnown();

		void notify(Subject *whoNotified) override;
};

#endif
