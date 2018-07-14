#include <cstdlib>
#include <sstream>
#include <fstream>

#include "board.h"

using namespace std;

Board::Board(ifstream &in)
	: disp{nullptr}, player{nullptr}, stairs{nullptr}, floor{1}, numChambers{5},
		playerRace{0}, customMap{false}, freeze{false}, gameOver{false}, playerWin{false}, in{in} {}

Board::~Board() {
	delete disp;

	delete player;

	for (auto &i : dead) delete i;

	for (auto &i : entities) delete i.second;

	for (auto &i : enemies) delete i.second;

	for (auto &i : tiles) delete i.second;

	for (auto &i : chambers) delete i;
}

//////////// INITIALIZATION /////////////

void Board::initEmpty(const string &source) {
	if (disp != nullptr) delete disp;

	ifstream base{source};

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
			if(!(base >> noskipws >> c)) return;

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

void Board::choosePlayer(char c, ifstream &file, bool cm) {
	playerRace = c;

	this->customMap = cm;

	initEmpty("cc3kfloorbase.txt");

	if (customMap) {
		this->generateFromFile(in);
	}

	else this->generateFloor();

	this->entities.erase(player->getCurPos());

	attachTiles(player);

  for (auto &i : this->treasures) {
    attachTiles(i.second);
  }

}
/////////////// GENERATION WITH FILE //////////////////

void Board::generateFromFile(ifstream &in) {
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

				// 0 - RH
				// 1 - BA
				// 2 - BD
				// 3 - PH
				// 4 - WA
				// 5 - WD
				// 6 - normal hoard
				// 7 - small hoard
				// 8 - merchant hoard
				// 9 - dragon Hoard

				// potions
				if (c >= '0' && c <= '5') {
					makePot(c - '0', p);
				}

				// nomral gold
				else if (c == '6') {
					Treasure *tre = new Treasure{p, 2, "normal"};
					treAttach(tre, p);
				}

				// small gold
				else if (c == '7') {
					Treasure *tre = new Treasure{p, 1, "small"};
					treAttach(tre, p);
				}

				// merchant hoard
				else if (c == '8') {
					Treasure *tre = new Treasure{p, 4, "merchant"};
					treAttach(tre, p);
				}

				// dragon hoard
				else if (c == '9') {
					Treasure *tre = new DragonHoard{p};
					treAttach(tre, p);
				}

				// player
				else if (c == '@') {
					this->makePlayer(p);
				}

				// stairs
				else if (c == 92) {
					this->makeStairs(p);
				}

				// enemies
				//	H - human
				//	W - dwarf
				//	E - elf
				//	O - orc
				//	M - merchant
				//	L - halfing
				//	D - dragon

				// human
				else if (c == 'H') {
					Enemy *en = new Human{p};
					this->enemies[p] = en;

					//attachThings(en, p);
				}

				// dwarf
				else if (c == 'W') {
					Enemy *en = new Dwarf{p};
					this->enemies[p] = en;

					//attachThings(en, p);
				}

				// elf
				else if (c == 'E') {
					Enemy *en = new Elf{p};
					this->enemies[p] = en;

					//attachThings(en, p);
				}

				// orc
				else if (c == 'O') {
					Enemy *en = new Orc{p};
					this->enemies[p] = en;

					//attachThings(en, p);
				}

				// merchant
				else if (c == 'M') {
					Enemy *en = new Merchant{p};
					this->enemies[p] = en;

					//attachThings(en, p);
				}

				// halfing
				else if (c == 'L') {
					Enemy *en = new Halfling{p};
					this->enemies[p] = en;

					//attachThings(en, p);
				}

				// dragon
				else if (c == 'D') {
					Enemy *en = new Dragon{p, nullptr};
					this->enemies[p] = en;

					//attachThings(en, p);
				}

				++x;
			}
		}
	}

	for (auto &i : enemies) {
		attachThings(i.second,i.first);
	}

}

void Board::treAttach(Treasure *tre, const Posn &p) {
	tre->attach(disp);
	this->treasures[p] = tre;
	this->entities[p] = tre;
	tre->notifyObservers(SubscriptionType::Display);
}


////////////////// GENERATION /////////////////////////

void Board::generateFloor() {

	// order is player, stairs, potions, gold, enemies

	// if no command line argument file

	this->generatePlayer();
	this->generatePotions();
	this->generateGold();
	this->generateEnemies();
}

// generates player and stairs
void Board::generatePlayer() {


	// get random chamber
	int playerChamber = (rand() % numChambers);

	// get random tile within chosen chamber
	Posn pp = chambers[playerChamber]->randomTile();

	// creates player on that tile
	/*
		(s)hade
		(d)row
		(v)amprie
		(t)roll
		(g)oblin
	*/

	this->makePlayer(pp);

	int stairsChamber = (rand() % numChambers);

	while(true) {
		if (stairsChamber != playerChamber) break;
		stairsChamber = (rand() % numChambers);
	}

	Posn sp = chambers[stairsChamber]->randomTile();

	// make stairs
	this->makeStairs(sp);

}

void Board::makePlayer(const Posn &pp) {
	switch(playerRace) {
		case 's': this->player = new Shade(pp); break;
		case 'd': this->player = new Drow(pp); break;
		case 'v': this->player = new Vampire(pp); break;
		case 't': this->player = new Troll(pp); break;
		case 'g': this->player = new Goblin(pp); break;
		case 'h': this->player = new Ghost(pp); break;
	}
	this->entities[pp] = player;

	// attach display to player observers
	player->attach(disp);
	player->notifyObservers(SubscriptionType::Display);
}

void Board::makeStairs(const Posn &sp) {
	this->stairs = new Stairs(sp);

	// attach display to stairs observers
	this->stairs->attach(disp);
	this->entities[sp] = stairs;

	this->stairs->notifyObservers(SubscriptionType::Display);
}

/////// Potions ////////

void Board::generatePotions() {

	// 10 potions are spawned on each floor.
	//	each type having 1/6 probability.
	//	each chamber has equal 1/5 probability.
	//	Each tile in the chamber has equal chance.

	int numPotions = 10;

	for (int i = 0; i < numPotions; ++i) {
		Posn p{0,0};
		// first pick chamber
		int potChamber = rand() % numChambers;

		// second pick tile
		while(true) {
			p = chambers[potChamber]->randomTile();
			if (p != player->getCurPos() && entities.count(p) == 0) break;
		}
		//	then pick type
		int whichPot = rand() % 6;

		makePot(whichPot, p);
	}
}

void Board::makePot(int whichPot, const Posn &p) {
	Potion *pot = nullptr;
	if (whichPot == 0) {
		pot = new RHPotion(p);
	}
	else if (whichPot == 1) {
		pot = new BAPotion(p);
	}
	else if (whichPot == 2) {
		pot = new BDPotion(p);
	}
	else if (whichPot == 3) {
		pot = new PHPotion(p);
	}
	else if (whichPot == 4) {
		pot = new WAPotion(p);
	}
	else if (whichPot == 5) {
		pot = new WDPotion(p);
	}
	pot->attach(disp);
	this->entities[p] = pot;

	// update display
	pot->notifyObservers(SubscriptionType::Display);
}

void Board::generateGold() {
	// 10 piles of gold
	// the spawn rate of gold is
	//	5/8 chance of normal,
	//	1/8 dragon hoard,
	//	1/4 small hoard.
	int numPiles = 10;

	for (int i = 0; i < numPiles; ++i) {
		Posn p{0,0};
		Treasure *tre = nullptr;
		//first pick chamber and tile
		int goldChamber = rand() % numChambers;

		while (true) {
			p = this->chambers[goldChamber]->randomTile();
			if (p != player->getCurPos() && this->entities.count(p) == 0) break;
		}

		// then pick type of gold.
		int goldType = rand() % 8;

		if (goldType < 5) {
			tre = new Treasure{p, 2, "normal"};
		}
		else if (goldType < 6) {
			tre = new DragonHoard{p};
		}
		else {
			tre = new Treasure{p, 1, "small"};
		}
		this->treAttach(tre, p);
	}
}


///////// ENEMIES ///////////

void Board::generateEnemies() {


	// DRAGONS
	for (auto &it : this->treasures) {
		Treasure *i = it.second;

		if (!i->canPickUp()){

			Posn dhp = i->getCurPos();

			Posn dp = randDir(dhp);

			while(true) {
				dp = randDir(dhp);
				if (this->tiles.at(dp)->getType() == '.'
						&& dp != this->player->getCurPos()
						&& this->entities.count(dp) == 0) {
					break;
				}
			}

			Enemy *en = new Dragon{dp, i};
			attachThings(en, dp);
		}
	}

	// other enemies
	// Human: 2/9,
	// Dwarf: 3/18
	// Halfling: 5/18
	// Elf: 1/9
	// Orc: 1/9
	// Merchant: 1/9
	int numEns = 20;
	for (int i = 0; i < numEns; ++i) {
		Posn p{0,0};
		Enemy *en;
		// first pick chamber
		int enChamber = rand() % numChambers;

		// then pick tile
		while(true) {
			p = chambers[enChamber]->randomTile();

			if (p != player->getCurPos()
					&& entities.count(p) == 0
					&& enemies.count(p) == 0) break;
		}

		// then enemy type
		int whichEn = rand() % 18;

		// create enemy
		if (whichEn < 4) {
			en = new Human{p};
		}
		else if (whichEn < 7) {
			en = new Dwarf{p};
		}
		else if (whichEn < 12) {
			en = new Halfling{p};
		}
		else if (whichEn < 14) {
			en = new Elf{p};
		}
		else if (whichEn < 16) {
			en = new Orc{p};
		}
		else {
			en = new Merchant{p};
		}

		attachThings(en, p);
	}



}

void Board::attachThings(Enemy *en, const Posn &p) {
	en->attach(this->disp);
	this->enemies[p] = en;
	this->attachTiles(en);
	en->notifyObservers(SubscriptionType::Display);
}

///////// MOVEMENT //////////

bool Board::movePlayer(const string &dir) {
  //reset tiles
  this->player->detachTiles();
  attachTiles(this->player);


	bool success = player->move(dir);
	if (success) {

		Posn pp = this->player->getCurPos();

		// CHECK IF STAIRS
		if (this->entities.count(pp) == 1  && this->entities.at(pp)->getType() == 92) {
			this->newFloor();
			return false;
		}

    attachTiles(player);

    this->player->notifyObservers(SubscriptionType::Enemy);
    this->player->notifyObservers(SubscriptionType::Dragon);
    this->player->notifyObservers(SubscriptionType::Potion);
    this->player->notifyObservers(SubscriptionType::Gold);

    if (this->entities.count(pp) == 1
				&& this->entities.at(pp)->getType() == 'G'
				&& this->treasures.at(pp)->canPickUp()) {

			this->dead.push_back(this->entities.at(pp));
  		this->entities.erase(pp);
  		this->treasures.erase(pp);
		}


		// update display
		this->player->notifyObservers(SubscriptionType::Display);

		// reverts tile moved from in display
		if (this->treasures.count(player->getLastPos()) == 1) {
			this->treasures.at(player->getLastPos())->notifyObservers(SubscriptionType::Display);
		}
		else {
			this->disp->notify(tiles.at(player->getLastPos()));
		}
	}
	return !success;
}


////////// MISC ////////////

void Board::attachTiles(Subject *s) {

	//cerr << s->getIcon() << " called attachTiles." << endl;

	Posn sp = s->getCurPos();
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			Posn tp = {x,y};
			tp = tp + sp;

			if (this->enemies.count(tp) == 1) {
				s->attach(tp, this->enemies.at(tp));
				//cerr << s->getIcon() << " attached an enemy." << endl;
			}

			else if (this->entities.count(tp) == 1) {
				s->attach(tp, this->entities.at(tp));
				//cerr << s->getIcon() << " attached an item." << endl;
			}

			else if (player->getCurPos() == tp && s->getIcon() != 'P') {
				s->attach(tp, player);
				//cerr << s->getIcon() << " attached a player." << endl;
			}

			else {
				s->attach(tp, tiles.at(tp));
				//cerr << s->getIcon() << " attached an empty tile." << endl;
			}
		}
	}
}

Posn Board::randDir(const Posn &p) {
	int r = rand() % 8;
	Posn np{0,0};

	if (r == 0) {
		np = {-1,-1};
	}
	else if (r == 1) {
		np = {-1, 0};
	}
	else if (r == 2) {
		np = {-1, 1};
	}
	else if (r == 3) {
		np = {0, 1};
	}
	else if (r == 4) {
		np = {1, 1};
	}
	else if (r == 5) {
		np = {1, 0};
	}
	else if (r == 6) {
		np = {1, -1};
	}
	else if (r == 7) {
		np = {0, -1};
	}

	return np = np + p;
}

///////// MISC //////////////

void Board::resetPlayer() {
	//reset tiles
  this->player->detachTiles();
  attachTiles(this->player);
  this->player->notifyObservers(SubscriptionType::Enemy);
  this->player->notifyObservers(SubscriptionType::Dragon);
  this->player->notifyObservers(SubscriptionType::Gold);
}

///////// COMBAT ////////////

bool Board::attack(const string &dir) {
  //reset tiles
  resetPlayer();

  Posn enPos = this->player->canAttack(dir, enemies);

  // check if there is an enemy there (attack went through)
  if (this->enemies.count(enPos) == 1) {
  	Enemy *en = this->enemies.at(enPos);
  	int hp = en->getHp();
  	// check if enemy hp is 0
  	if (hp == 0) {
  		dead.push_back(en);
  		entities.erase(enPos);
  		enemies.erase(enPos);
  		//en->deathEffect();
  		this->tiles.at(enPos)->notifyObservers(SubscriptionType::Display);
			attachTiles(this->player);
  	}
  	return false;
	}
	return true;
}

void Board::actionEnemy() {

	map<Posn, Enemy *> temp = this->enemies;

	//int i = 0;
  for (auto &it : this->enemies) {

  	//++i;
  	Enemy *en = it.second;

     //reset tiles
    en->detachTiles();
    attachTiles(en);

  	en->detachTiles();
  	attachTilesTemp(en, temp);

  	// checks if near player
    if(en->isNearPlayer() && en->isHostile()) {
      stringstream ss;
      int dmg = en->attack(this->player);

      // printing action:
      ss << en->getRace() << " dealt " << dmg << " damage to "
       << this->player->getRace() << " (" << this->player->getHp() << " HP)";

      this->player->appendAction(ss.str());
      en->detachTiles();
  		attachTilesTemp(en, temp);
    }

    // if the enemy doesnt attack player, move the enemy
    else if (!freeze) {
    	// first pick spot for enemy to move

    	// if dragon then move on
    	if (en->getType() == 'D') continue;
    	// attempt to move

    	// want to:
    	//	get random positon to move to
    	//	try to move there with en->move(np)
    	//	might move or not
    	//  before attempt, detach and attachtiles from temp
    	//	TRY AGAIN TO MOVE PLAYER
    	//		IF SUCCESSFUL:
    	//			need to add new location on enemy map
    	//			remove old location
    	//			update display to revert LAST position
    	// ALWAYS WANT TO ATTACH TILES

    	// try 10 times to get a movement spot
    	for (int i = 0; i < 10; ++i) {
	    	Posn np{0,0};
	    	np = randDir(en->getCurPos());

	    	// detaches tiles
	    	bool success = en->move(np);

	    	//cout << "(" << i << ") " << (success ? "ENEMY MOVED" : "NO ENEMY MOVE :(") << endl;

	 			// on success, change location of enemy in temp map, erase last location,
	 			//	change last location of display to previous thing.
	    	if (success && !(en->getLastPos() == en->getCurPos())) {
	    		temp[np] = en;
	    		temp.erase(en->getLastPos());
	    		disp->notify(tiles.at(en->getLastPos()));
	    		break;
	    	}
	    	// attaches tiles from temp
    		attachTilesTemp(en, temp);
	    }
    }
    en->setNearPlayer(false);
  }
  this->enemies = temp;
  this->player->notifyObservers(SubscriptionType::Display);
}

void Board::attachTilesTemp(Subject *s, map<Posn, Enemy*> &ens) {
	Posn sp = s->getCurPos();
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			Posn tp = {x,y};
			tp = tp + sp;

			if (ens.count(tp) == 1) {
				s->attach(tp, ens.at(tp));
				//cerr << s->getIcon() << " attached an enemy." << endl;
			}

			else if (this->entities.count(tp) == 1) {
				s->attach(tp, this->entities.at(tp));
				//cerr << s->getIcon() << " attached an item." << endl;
			}

			else if (player->getCurPos() == tp && s->getIcon() != 'P') {
				s->attach(tp, player);
				//cerr << s->getIcon() << " attached a player." << endl;
			}

			else {
				s->attach(tp, tiles.at(tp));
				//cerr << s->getIcon() << " attached an empty tile." << endl;
			}
		}
	}
}

/////////// POTIONS ///////////

bool Board::use(const string &dir) {

	Posn potPos = this->player->use(dir);
	bool failed = true;

	if (entities.count(potPos) == 1 &&
		entities.at(potPos)->getType() == 'P') {

		this->resetPlayer();

		this->dead.push_back(entities.at(potPos));
		this->entities.erase(potPos);
		failed = false;
	}

	this->tiles.at(potPos)->notifyObservers(SubscriptionType::Display);
	attachTiles(this->player);
	return failed;
}

////////////////////////////////


void Board::displayBoard() const {
	cout << *disp;
}

Tile* Board::getTile(const Posn &p) const {
	return tiles.at(p);
}

void Board::clearAction() {
	this->player->setAction("");
}


/////////////// NEW FLOOR //////////////////

void Board::newFloor() {
	++this->floor;
	cerr << this->floor << endl;
	if (this->floor <= 5) { // check if the floor number is ≤ 5
    // update floor number

    // delete old player after saving HP
    int curHp = this->player->getHp();  // to be used after new copy of player is made
    int curGold = this->player->getGold(); // to be used after SHUT UP JOYCE

    Player *oldPlayer = this->player;
    this->player = nullptr;
    delete oldPlayer;

        // delete dead
  	for (auto &i : dead) delete i;
    this->dead.clear();

    // delete entities
    for (auto &i : entities) delete i.second;
    this->entities.clear();

  	for (auto &i : tiles) delete i.second;
    this->tiles.clear();

  	for (auto &i : chambers) delete i;
    this->chambers.clear();

  	for (auto &i : enemies) delete i.second;
    this->enemies.clear();

  	this->treasures.clear();

    this->choosePlayer(this->playerRace, this->in, this->customMap);

    // update new Player created with right HP
    player->setHp(curHp);
    player->pickUpGold(curGold);
    player->setFloor(floor);

  }
  else {  // end game

		this->gameOver = true;
		this->playerWin = true;
	}
}

double Board::generateScore() {
  if (this->player->getRace() == "Shade") {
    return 1.5 * double(this->player->getGold());
  }
  else {
    return double(this->player->getGold());
  }
}

void Board::toggleFreeze() {
	this->freeze = !this->freeze;
}

bool Board::isGameOver() {
	if (this->player->getHp() == 0) {
		this->gameOver = true;
	}
	return this->gameOver;
}

bool Board::wonGame() {
	return playerWin;
}

void Board::noHostile() {
	Merchant::noHostile();
}


