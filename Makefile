CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = cc3k
OBJECTS = main.o board.o display.o posn.o subject.o observer.o tile.o chamber.o\
entity.o stairs.o character.o player.o enemy.o shade.o drow.o vampire.o goblin.o troll.o ghost.o\
elf.o merchant.o dragon.o human.o orc.o dwarf.o halfling.o item.o potion.o bapotion.o\
bdpotion.o wapotion.o wdpotion.o rhpotion.o phpotion.o treasure.o dragonhoard.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS}
.PHONY: clean