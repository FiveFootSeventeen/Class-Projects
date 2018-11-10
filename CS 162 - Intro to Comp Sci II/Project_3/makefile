CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = gameMain.cpp FantasyGame.cpp Barbarian.cpp BlueMen.cpp Character.cpp HarryPotter.cpp Vampire.cpp \
Medusa.cpp checkNum.cpp menu.cpp 

HEADERS = checkNum.hpp menu.hpp FantasyGame.hpp Barbarian.hpp BlueMen.hpp Character.hpp HarryPotter.hpp \
Vampire.hpp Medusa.hpp


FantasyGame: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o FantasyGame
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck FantasyGame
	
clean:
	rm FantasyGame
