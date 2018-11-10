CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = searchSortMain.cpp SearchSort.cpp checkNum.cpp menu.cpp 

HEADERS = SearchSort.hpp checkNum.hpp menu.hpp 

searchSort: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o searchSort
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck searchSort
	
clean:
	rm searchSort
