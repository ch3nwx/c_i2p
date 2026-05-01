CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2

all: solution

solution: function.cpp 14927.cpp 14927.h
	$(CXX) $(CXXFLAGS) function.cpp 14927.cpp -o solution

run: solution
	./solution

clean:
	rm -f solution
