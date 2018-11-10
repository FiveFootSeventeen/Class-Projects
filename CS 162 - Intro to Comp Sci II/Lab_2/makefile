CXX = g++
CXXFLAGS = -std=c++0x 

SRCS = count_Letters.cpp count_Paragraph.cpp output_Letters.cpp fileIOMain.cpp

HEADERS = count_Letters.hpp count_Paragraph.hpp output_Letters.hpp


fileIO: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o fileIO
	
clean:
	rm fileIO


