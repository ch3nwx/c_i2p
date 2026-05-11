CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

all: solution

solution: function.cpp 14224.cpp 14224.h
	$(CXX) $(CXXFLAGS) function.cpp 14224.cpp -o solution

run: solution
	./solution

clean:
	rm -f solution
