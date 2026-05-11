CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

all: solution

solution: function.cpp 13858.cpp 13858.h
	$(CXX) $(CXXFLAGS) function.cpp 13858.cpp -o solution

run: solution
	./solution

clean:
	rm -f solution
