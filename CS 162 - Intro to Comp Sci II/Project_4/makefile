CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = gameMain.cpp FantasyTournament.cpp Barbarian.cpp BlueMen.cpp Character.cpp HarryPotter.cpp Vampire.cpp \
Medusa.cpp checkNum.cpp menu.cpp LosingChar.cpp CharacterList.cpp

HEADERS = checkNum.hpp menu.hpp FantasyTournament.hpp Barbarian.hpp BlueMen.hpp Character.hpp HarryPotter.hpp \
Vampire.hpp Medusa.hpp LosingChar.hpp CharacterList.hpp


FantasyTournament: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o FantasyTournament
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck FantasyTournament
	
clean:
	rm FantasyTournament
