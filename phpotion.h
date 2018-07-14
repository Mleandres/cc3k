#ifndef __PHPOTION_H__
#define __PHPOTION_H__
#include "potion.h"

class PHPotion final : public Potion{
	static bool known;

	public:
		PHPotion(Posn p);
		void use(Player &p) override;

		bool isKnown();

		void notify(Subject *whoNotified) override;
};

#endif
