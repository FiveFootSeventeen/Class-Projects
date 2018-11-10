CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = recursionMain.cpp recurse.cpp menu.cpp checkNum.cpp 

HEADERS = recurse.hpp menu.hpp checkNum.hpp 


recursion: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o recursion
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck recursion
	
clean:
	rm recursion
