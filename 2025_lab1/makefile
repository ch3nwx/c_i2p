# Complier and Flags
CXX = gcc
CXXFLAGS = -std=c++17 -Wall -g -w

# Files
SRCS = reverse.c 14575.c
OBJS = $(SRCS:.c=.o)
TARGET = reverse

#default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

#clean
clean:
	rm -f $(OBJS) $(TARGET)


# g++ -std=c++17 -Wall -g main.cpp square.cpp -o app

