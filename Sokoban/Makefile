CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic -g

SFML_INCLUDE = -I/usr/local/include
SFML_LIB_PATH = -L/usr/local/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

MAIN_SRC = main.cpp
SOKOBAN_SRCS = Sokoban.cpp
TEST_SRC = test.cpp

MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
SOKOBAN_OBJS = $(SOKOBAN_SRCS:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

SOKOBAN_EXE = Sokoban
SOKOBAN_LIB = Sokoban.a
TEST_EXE = test

all: $(SOKOBAN_EXE) $(TEST_EXE)

$(SOKOBAN_EXE): $(MAIN_OBJ) $(SOKOBAN_LIB)
	$(CXX) $(CXXFLAGS) $(SFML_LIB_PATH) $(MAIN_OBJ) $(SOKOBAN_LIB) -o $@ $(SFML_LIBS)

$(SOKOBAN_LIB): $(SOKOBAN_OBJS)
	ar rcs $@ $(SOKOBAN_OBJS)

$(TEST_EXE): $(TEST_OBJ) $(SOKOBAN_LIB)
	$(CXX) $(CXXFLAGS) $(SFML_LIB_PATH) $(TEST_OBJ) $(SOKOBAN_LIB) -o $@ -lboost_unit_test_framework $(SFML_LIBS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -c $< -o $@

clean:
	rm -f $(MAIN_OBJ) $(SOKOBAN_OBJS) $(TEST_OBJ) $(SOKOBAN_EXE) $(SOKOBAN_LIB) $(TEST_EXE)

lint:
	cpplint *.cpp *.hpp


.PHONY: all clean lint
