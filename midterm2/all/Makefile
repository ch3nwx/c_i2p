CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

all: solution

solution: function.cpp question.cpp question.h
	$(CXX) $(CXXFLAGS) function.cpp question.cpp -o solution

clean:
	rm -f solution
