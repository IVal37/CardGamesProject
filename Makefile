CXX := g++
CXXFLAGS := -std=c++17 -g -Wall -Wextra -Werror

TARGET := poker

SOURCES := main.cpp \
           Poker.cpp \
           Player.cpp \
           Deck.cpp \
           Card.cpp \
           Util.cpp

OBJECTS := $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean