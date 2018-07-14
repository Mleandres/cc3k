#include <cstdlib>
#include <ctime>

#include "board.h"

using namespace std;

Board::Board() : disp{nullptr}, player{nullptr}, numChambers{5} {}

Board::~Board() {
	delete disp;

	delete player;

	for (auto i : tiles) delete &i;

	for (auto i : chambers) delete &i;
}

void Board::initEmpty(string &source) {
	if (disp != nullptr) return;

	ifstream in{source};

	disp = new Display;

	int h = 0;
	int w = 0;

	disp->getHW(h,w);

	// each row
	for (int y = 0; y < h; ++y) {
		// each column
		for (int x = 0; x < w;) {
			Posn p{x,y};
			char c;
			if(!(in >> noskipws >> c)) return;

			if(c != '\n') {
				tiles[p] = new Tile{p,c};
				tiles.at(p)->attach(disp);

				disp->updateDisplay(p,c);
				++x;
			}
		}
	}

	for (int i = 1; i <= numChambers; ++i) {
		chambers.push_back(new Chamber(this, i));
		//cout << *(chambers.at(i));
	}

}

void move(string dir) {

  int newX = 0;
  int newY = 0;

  if(dir[0] == 'n') {
    newY += -1; //move up
  } 
  else if (dir[0] == 's') {
    newY += 1; //move down
  }

  if(dir[1] == 'w') {
    newX += -1; //move up
  } 
  else if (dir[1] == 'e') {
    newX += 1; //move down
  }

  Posn playerPosn = this->player->getPosn();
  newX += playerPosn.x;
  newY += playerPosn.y;

  player.move(this->tiles.at(Posn(newX, newY)));
}

void Board::choosePlayer(char c) {
	string file = "cc3kfloorbase.txt";

	initEmpty(file);
	generateFloor();
}

void Board::generateFloor() {
	// order is player, stairs, potions, gold, enemies
	generatePlayer();
	/*
	generateStairs();
	generatePotions();
	generateGold();
	generateEnemies();
	*/
}

void Board::generatePlayer() {
	Posn p{10, 5};
	this->player = new Goblin(p);
	tiles.at(p)->notifyComing(player);

}

void Board::displayBoard() const {
	cout << *disp;
}

Tile* Board::getTile(Posn p) const {
	return tiles.at(p);
}

