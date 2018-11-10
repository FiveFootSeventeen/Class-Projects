CXX = g++
CXXFLAGS = -std=c++0x 
#CXXFLAGS += -wall			#Turns on all warnings
#CXXFLAGS += -pedantic-errors	#Strictly enforce the standard
#CXXFLAGS += -g
#LDFLAGS = -lboost_date_time

SRCS = osuInfoSystemMain.cpp University.cpp Instructor.cpp \
Student.cpp Person.cpp checkNum.cpp menu.cpp

HEADERS = University.hpp Building.hpp Instructor.hpp Student.hpp \
Person.hpp menu.hpp checkNum.hpp


osuInfoSystem: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o osuInfoSystem
	
.PHONY: valgrind
valgrind:
	valgrind --tool=memcheck osuInfoSystem
	
.PHONY: clean
clean:
	rm osuInfoSystem
