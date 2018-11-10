CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = stldemoMain.cpp queueStack.cpp checkNum.cpp menu.cpp 

HEADERS = queueStack.hpp checkNum.hpp menu.hpp 

stlDemo: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o stlDemo
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck stlDemo
	
clean:
	rm stlDemo
