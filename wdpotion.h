#ifndef __WDPOTION_H__
#define __WDPOTION_H__
#include "potion.h"

class WDPotion final : public Potion{
	static bool known;

	public:
	  WDPotion(Posn p);
		void use(Player &p) override;

		bool isKnown();

		void notify(Subject *whoNotified) override;
};

#endif
