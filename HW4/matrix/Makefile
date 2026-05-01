CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2

all: solution

solution: function.cpp 14605.cpp 14605.h
	$(CXX) $(CXXFLAGS) function.cpp 14605.cpp -o solution

run: solution
	./solution

clean:
	rm -f solution
