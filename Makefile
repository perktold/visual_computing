CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/usr/include/opencv5 $(shell pkg-config --cflags opencv5)
LDLIBS = $(shell pkg-config --libs opencv5)

TARGET = main
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
