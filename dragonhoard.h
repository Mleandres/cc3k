#ifndef __DRAGONHOARD_H__
#define __DRAGONHOARD_H__

#include "treasure.h"

class DragonHoard final : public Treasure{
	bool dragonSlain;
public:
	DragonHoard(Posn p);

	void notify(Subject *whoNotified) override;
};

#endif
