CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17

SRCS=utils.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)
DEPS=utils.h

TARGET=mancala

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
