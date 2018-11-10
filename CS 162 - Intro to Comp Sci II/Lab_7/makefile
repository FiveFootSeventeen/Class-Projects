CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = queueMain.cpp Queue.cpp checkNum.cpp menu.cpp 

HEADERS = Queue.hpp checkNum.hpp menu.hpp 

myQueue: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o myQueue
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck myQueue
	
clean:
	rm myQueue
