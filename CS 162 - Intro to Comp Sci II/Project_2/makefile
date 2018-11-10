CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = zooTycoonMain.cpp Zoo.cpp Animal.cpp Tiger.cpp Penguin.cpp Turtle.cpp checkInt.cpp intMenu.cpp

HEADERS = Zoo.hpp Animal.hpp Tiger.hpp Penguin.hpp Turtle.hpp intMenu.hpp checkInt.hpp


zooTycoon: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o zooTycoon
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck zooTycoon
	
clean:
	rm zooTycoon
