#ifndef __CHAMBER_H__
#define __CHAMBER_H__

#include <map>
#include <vector>
#include <iostream>

#include "board.h"
#include "posn.h"
#include "tile.h"

class Board;

struct Posn;

class Chamber {
	Board *b; // pointer to board to get tiles

	const int type; // which chamber is it?

	Posn p; // chamber position on board (anchored at top left)

	int numEmpty; // number of emptyTiles
	int h;
	int w;

	// vvvv to delete later vvvv
	std::map<Posn, Tile*> emptyTiles; // Posns are local to amber.
	// ^^^^ to delete taler ^^^^

	std::vector<Tile*> chamberTiles;

	// puts empties in emptyTiles
	void fillEmpties();

	// checks if a tile is already in a chamber
	bool notInChamber(Tile *t) const;

public:

	Posn getPosn() const;

	int getType() const;
	int getNumEmpty() const;

	Tile* getEmptyTile(Posn p);

	Posn randomTile() const;

	Chamber(Board *b, int type); // so it knows which chamber is being constructed
	~Chamber(); // Dtor doesn't delete tiles

	friend std::ostream &operator<<(std::ostream &out, const Chamber &c);

};

#endif
