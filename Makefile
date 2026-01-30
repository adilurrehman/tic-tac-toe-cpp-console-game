CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra
TARGET = tictactoe
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) users.dat highscores.dat

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
