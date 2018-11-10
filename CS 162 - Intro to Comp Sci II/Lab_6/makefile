CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = dblLinkListMain.cpp DoubleList.cpp Node.cpp checkNum.cpp menu.cpp 

HEADERS = checkNum.hpp menu.hpp DoubleList.hpp Node.hpp

doubleList: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o doubleList
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck doubleList
	
clean:
	rm doubleList
