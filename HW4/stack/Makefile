CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2

all: solution

solution: function.cpp 10998.cpp 10998.h
	$(CXX) $(CXXFLAGS) function.cpp 10998.cpp -o solution

run: solution
	./solution

clean:
	rm -f solution
