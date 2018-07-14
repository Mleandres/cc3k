#ifndef __BOARD_H__
#define __BOARD_H__

#include "common.h"

/*
#include "passage.h"
#include "entity.h"
*/

class Display;
class Chamber;
class Player;

class Board {

	Display *disp;

	std::map<Posn, Tile*> tiles;
	std::map<Posn, Observer *> entities;
  std::map<Posn, Enemy *> enemies;
  std::map<Posn, Treasure *> treasures;

  std::vector<Chamber *> chambers;
	std::vector<Observer *> dead;

	Player *player;
	Stairs *stairs;

	int floor;
	const int numChambers;
	char playerRace;

	bool customMap;
	bool freeze;
	bool gameOver;
	bool playerWin;

	std::ifstream &in;

	void initEmpty(const std::string &source);

// generation
	void generateFloor();
	void generatePlayer();
	void generatePotions();
	void generateGold();
	void generateEnemies();

	void generateFromFile(const std::string &file);

// misc

	// attaches adjacent entities or tiles to subject's observers
	void attachTiles(Subject *s);

	// specifically for enemy movement
	void attachTilesTemp(Subject *s, std::map<Posn, Enemy*> &ens);

	// finds the posn of a random tile location in a direction
	Posn randDir(const Posn &p);

	// attaches things to enemies
	void attachThings(Enemy *en, const Posn &p);

	// resets player tiles
	void resetPlayer();

	// goes to new floor!

	void newFloor();

	// makes a potion
	void makePot(int whichPot, const Posn &p);

	// makes player
	void makePlayer(const Posn &pp);

	// makes stairs
	void makeStairs(const Posn &sp);

	// attaches treasure
	void treAttach(Treasure *tre, const Posn &p);

	// generates from file
	void generateFromFile(std::ifstream &in);

public:

	Board(std::ifstream &in);
	~Board();

	//int getCurFloor() const;

	//Player Character choices:
	void choosePlayer(char c, std::ifstream &in, bool cm);

	bool movePlayer(const std::string &dir);

	// randomly generates board
	void generateBoard();

	bool attack(const std::string &dir);
	bool use(const std::string &dir);

	// displays board to cout
	void displayBoard() const;

	// gets pointer to Tile at p
	Tile* getTile(const Posn &p) const;

	// makes enemies do their actions
	void actionEnemy();

	void clearAction();

	double generateScore();

	void toggleFreeze();

	bool isGameOver();

	bool wonGame();

	void noHostile();

};

#endif
