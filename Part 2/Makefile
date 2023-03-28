# ML-FE-BE_2 Makefile
CXX      = g++
CXXFLAGS = -Wall -std=c++17
TARGET	 = ../game_p2
SRC	 = ML-FE-BE_2.cpp

ifeq ($(OS),Windows_NT)
  TARGET = ../game_p2_win32
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
     TARGET = ../game_p2_linux
  endif
  ifeq ($(UNAME_S),Darwin)
     TARGET = ../game_p2_osx
  endif
endif


$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)