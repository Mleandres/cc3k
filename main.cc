#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "board.h"

using namespace std;

bool handleArgs(int argc, char* argv[], bool &dlcEnabled, string &source){
	bool customMap = false;

	for (int i = 1; i < argc; ++i) {
		string argument;
		istringstream ss{argv[i]};
		argument = ss.str();
		if (argument == "-dlc") {
			dlcEnabled = true;
		}
		else {
			source = argument;
			customMap = true;
		}
	}
	return customMap;
}


int main(int argc, char *argv[]){
	srand(time(0));

	bool customMap = false;
	bool dlcEnabled = false;

	while(true) {
		bool restart = false;
		bool quit = false;

		string cmd;
		char beg;

		string source = "cc3kfloorbase.txt";

		cout << endl;
		for (int i = 0; i < 52; ++i) cout << "=";
		cout << endl;
		cout << ">>>>>>>> ";
		cout << "WELCOME TO CC3K - DAY ONE EDITION™";
		cout << " <<<<<<<<" << endl;
		for (int i = 0; i < 52; ++i) cout << "=";
		cout << endl << endl;
		cout << "Thank you for purchasing this Early Access™ title!" << endl;
		cout << "From CMJ Family Inc™" << endl;
		cout << endl;

		customMap = handleArgs(argc, argv, dlcEnabled, source);

		ifstream in{source};

		Board b{in};

		// init commands
		while(true) {

			cout << "To start the game," << endl;
			cout << "please enter a character to select a race:" << endl;
			cout << "(s)hade (hard)" << endl;
			cout << "(d)row (med)" << endl;
			cout << "(v)ampire (med)" << endl;
			cout << "(t)roll (easy)" << endl;
			cout << "(g)oblin (hard)" << endl;

			if (dlcEnabled) {
				cout << "g(h)ost (??" << "?)" << endl;
			}

			cout << endl;
			cout << "or:" << endl;
			cout << "(q)uit" << endl;
			cout << endl;

			cin >> beg;

			// end of file case
			if (cin.eof()) {
				cerr << "End of file detected. Exiting." << endl;
				return 0;
			}
			// shade
			else if (beg == 's'){
				break;
			}

			// drow
			else if (beg == 'd') {
				break;
			}

			// vamp
			else if (beg == 'v') {
				break;
			}

			// troll
			else if (beg == 't') {
				break;
			}
			// goblin
			else if (beg == 'g') {
				break;
			}

		// DLC characters
			// ghost
			else if (beg == 'h' && dlcEnabled) {
				break;
			}

			// quit

			else if (beg == 'q') {
				quit = true;
				break;
			}

			else {
				cout << "Invalid input! Please try again. (or enter 'q' to quit)" << endl;
				cout << endl;
				cin.clear();
				cin.ignore();
			}
		}

		if (quit) break;

		b.choosePlayer(beg, in, customMap);
		b.displayBoard();

		// commands while running
		string dir = "";
		bool attack = false;
		bool use = false;
		while (cin >> cmd) {
			bool failed = false;

			// just in case
			restart = false;
			quit = false;

			cerr << (b.wonGame() ? "ok" : "not ok") << endl;

			if (b.wonGame()) {
				cout << "You won!" << endl;
				double score = b.generateScore();
				cout << "Your score: " << score << endl;
				restart = false;
				quit = true;
				break;
			}
			else if (b.isGameOver()) {
				cout << "Game over!" << endl;
				cout << "Would you like to (r)estart or (q)uit?" << endl;
				char l;
				cin >> l;
				if (l == 'r') {
					restart = true;
					break;
				}
				else {
					quit = true;
					break;
				}
			}


			// take commands
			if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" ||
					cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {

				dir = cmd;
				if (attack) {
					failed = b.attack(dir);
					attack = false;
				}
				else if (use) {
					failed = b.use(dir);
					use = false;
				}
				else {
	        failed = b.movePlayer(dir);
	      }

				if (!failed) b.actionEnemy();

				b.displayBoard();
			}

			else if (cmd == "u") {
				attack = false;
				use = true;
			}
			else if (cmd == "a") {
				use = false;
				attack = true;
			}

			// enemies stop moving
			else if (cmd == "f") b.toggleFreeze();

			// restart game
			else if (cmd == "r") {
				restart = true;
				break;
			}

			// quit while game is running
			else if (cmd == "q") {
				quit = true;
				break;
			}
			else {
				cout << "Invalid input. Please try again." << endl;
			}

			b.clearAction();

			// Check if game has ended

		}


		if (restart) {
			b.noHostile();
			continue;
		}
		else if (quit) break;

	}

	cout << endl;
	cout << "Exiting game..." << endl;
	cout << "Thanks for playing!" << endl;
	cout << endl;
}
