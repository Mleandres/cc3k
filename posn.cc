#include "posn.h"

Posn::Posn(int x, int y) : x{x}, y{y} {}

bool Posn::operator<(const Posn &rhs) const {
	if (y < rhs.y) return true;
	if (y == rhs.y) return x < rhs.x;
	return false;
}

bool Posn::operator==(const Posn &rhs) const {
	if (x != rhs.x) return false;
	if (y != rhs.y) return false;
	return true;
}

bool Posn::operator!=(const Posn &rhs) const {
	return !(*this == rhs);
}

Posn Posn::operator+(const Posn &rhs) const {
	Posn ret{x, y};

	ret.x += rhs.x;
	ret.y += rhs.y;
	return ret;
}

std::ostream &operator<<(std::ostream &out, const Posn &p) {
	out << "(" << p.x << "," << p.y << ")";
	return out;
}
