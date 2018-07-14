#ifndef __ROOM_H__
#define __ROOM_H__

#include "posn.h"

struct Posn;

// Abstract Base class for chamber and passage
class Room {
	Posn p;

public:

	// gets the value of the position
	Posn getPosn() const = 0;




};

#endif
