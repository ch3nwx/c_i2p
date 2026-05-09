CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

all: solution

solution: function.cpp 13182.cpp 13182.h
	$(CXX) $(CXXFLAGS) function.cpp 13182.cpp -o solution

run: solution
	./solution

clean:
	rm -f solution
