CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = warGameMain.cpp LoadedDie.cpp intMenu.cpp Game.cpp Die.cpp checkInt.cpp

HEADERS = LoadedDie.hpp intMenu.hpp Game.hpp Die.hpp checkInt.hpp


warGame: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o warGame
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck warGame
	
clean:
	rm warGame
