#ifndef __BAPOTION_H__
#define __BAPOTION_H__
#include "potion.h"

class BAPotion final : public Potion{
	static bool known;

	public:
	  BAPotion(Posn p);
		void use(Player &p) override;

		bool isKnown();

		void notify(Subject *whoNotified) override;
};

#endif
