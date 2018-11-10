CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = fibFunct.cpp fibonacciMain.cpp checkNum.cpp menu.cpp 

HEADERS = fibFunct.hpp checkNum.hpp menu.hpp 

fibFunct: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o fibFunct
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck fibFunct
	
clean:
	rm fibFunct
