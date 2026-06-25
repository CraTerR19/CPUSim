CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = cpusim.exe
SOURCES = main.cpp Task.cpp Parser.cpp Cache.cpp Scheduler.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	del /f $(TARGET) 2>nul

.PHONY: clean
