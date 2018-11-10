CXX = g++
CXXFLAGS = -std=c++0x 

SRCS = matrixCalculatorMain.cpp readMatrix.cpp determinant.cpp checkInt.cpp

HEADERS = determinant.hpp readMatrix.hpp checkInt.hpp


matrixCalculator: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o matrixCalculator
	
clean:
	rm matrixCalculator


