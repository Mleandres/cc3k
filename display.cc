#include "display.h"

using namespace std;

Display::Display()
: theDisplay{}, h{25}, w{79}, s{0,0,0,0,1,"",""} {}

Display::~Display() {}

SubscriptionType Display::getSubType() const {
	return SubscriptionType::Display;
}

void Display::updateDisplay(const Posn &p, char c) {
	theDisplay[p] = c;
}

void Display::notify(Subject *whoNotified) {
	Posn curPos = whoNotified->getCurPos();
	//Posn lastPos = whoNotified->getLastPos();
	char c = whoNotified->getIcon();

	Stats other = whoNotified->getStats();
	if (other.hp != -1) s = other;

	updateDisplay(curPos, c);
}

char Display::getType() const {
	return 0;
}

std::ostream &operator<<(std::ostream &out, const Display &d) {

	for (int y = 0; y < d.h; ++y) {
		for (int x = 0; x < d.w; ++x) {
			Posn p{x,y};
			out << d.theDisplay.at(p);
		}
		out << endl;
	}

	out << "Race: " << d.s.race;
	out << " Gold: " << d.s.gold;

	for (int i = 0; i < 47; ++i) {
		out << " ";
	}
	out << "Floor: " << d.s.floor << endl;

	out << "HP: " << d.s.hp << endl;
	out << "Atk: " << d.s.att << endl;
	out << "Def: " << d.s.def << endl;
	out << "Action: " << d.s.action << "." << endl;
	out << endl;
	return out;
}


/*
void Display::notifyComing(Subject *whoNotified) {
	this->theDisplay[whoNotified->getPosn()] = whoNotified->getType();
}

void Display::notifyLeave() {
	return;
}
*/

void Display::getHW(int &height, int &width) {
	height = h;
	width = w;
}
