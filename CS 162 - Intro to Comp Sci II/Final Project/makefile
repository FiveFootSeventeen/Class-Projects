CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = cakeMain.cpp Dungeon.cpp Practice.cpp Challenge.cpp Gameplay.cpp Map.cpp Player.cpp \
Space.cpp checkNum.cpp menu.cpp 

HEADERS = Dungeon.hpp Practice.hpp Challenge.hpp Gameplay.hpp Map.hpp Player.hpp \
Space.hpp checkNum.hpp menu.hpp names.hpp


cakeGame: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -lncurses -o cakeGame
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck cakeGame
	
clean:
	rm cakeGame
