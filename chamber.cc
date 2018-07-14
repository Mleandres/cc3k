#include <cstdlib>
#include <ctime>

#include "chamber.h"

using namespace std;

Chamber::Chamber(Board *b, int type)
	: b{b}, type{type}, p{0,0}, numEmpty{0}, h{0}, w{0} {

	if (type == 1) {
		p = {2,2};
		h = 6;
		w = 28;
	}

	else if (type == 2) {
		p = {37, 9};
		h = 5;
		w = 14;
	}

	else if (type == 3) {
		p = {38, 2};
		w = 39;
		h = 12;
	}

	else if (type == 4) {
		p = {3, 14};
		w = 23;
		h = 9;
	}

	else if (type == 5) {
		p = {36,15};
		w = 41;
		h = 8;
	}

	fillEmpties();
}

Chamber::~Chamber() {}

void Chamber::fillEmpties() {
	// each row (first will always be a wall)
	for (int y = 0; y < h; ++y) {

		// each column (first will always be a wall)
		for (int x = 0; x < w; ++x) {

			Posn lp = {x,y}; // local pos (tile relative to chamber)
			Posn gp = p + lp; // global pos (tile relative to board)

			// get tile at posn from board

			Tile *t = b->getTile(gp);

			char c = t->getType();

			// check if empty, (c == '.') // else do nothing and move on.

			if (c == '.' && notInChamber(t)) {
				// add to map (delete later??)
				emptyTiles[gp] = t;

				// add to vector tiles
				chamberTiles.push_back(t);
				t->setChamber(type);
				++numEmpty;
			}
		}
	}
}

Posn Chamber::randomTile() const {
	int whichTile = (rand() % numEmpty);

	return chamberTiles[whichTile]->getPosn();
}

bool Chamber::notInChamber(Tile *t) const {
	if (t->getChamber() == 0) return true;
	return false;
}

ostream &operator<<(ostream &out, const Chamber &c) {
	for (int y = 0; y < 25; ++y) {
		for (int x = 0; x < 79; ++x) {
			Posn p{x,y};
			if (c.emptyTiles.count(p) == 0) out << " ";
			else out << c.emptyTiles.at(p)->getType();
		}
		out << endl;
	}
	return out;
}

