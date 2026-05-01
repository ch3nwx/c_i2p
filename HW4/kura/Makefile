CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

all: solution

solution: function.cpp 14931.cpp 14931.h
	$(CXX) $(CXXFLAGS) function.cpp 14931.cpp -o solution

run: solution
	./solution

clean:
	rm -f solution
