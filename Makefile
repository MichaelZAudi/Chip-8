# compiler options
CXXFLAGS = -g -Wall -Wextra
CXXFLAGS += -std=c++17 -pedantic -pedantic-errors
CXXFLAGS += -Wfloat-equal -Wredundant-decls -Wshadow -Wconversion

# list .h files here
HEADERS = chip8.h display.h

# list .cpp files here
PROGRAM_FILES = main.cpp chip8.cpp display.cpp

.PHONY: all
all: program.exe

program.exe: $(PROGRAM_FILES) $(SHARED_FILES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(PROGRAM_FILES) $(SHARED_FILES) `sdl2-config --cflags --libs` -o $@

.PHONY: clean
clean:
	rm -f program.exe