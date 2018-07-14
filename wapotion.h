#ifndef __WAPOTION_H__
#define __WAPOTION_H__
#include "potion.h"

class WAPotion final : public Potion{
	static bool known;

	public:
	  WAPotion(Posn p);
		void use(Player &p) override;

		bool isKnown();

		void notify(Subject *whoNotified) override;
};

#endif
