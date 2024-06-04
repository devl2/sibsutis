CC = g++
CFLAGS = -Wall -Wextra -std=c++2a -pthread

SFML_DIR = external/SFML
SFML_INCLUDE = -I$(SFML_DIR)/include
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

GTEST_DIR = external/googletest
GTEST_BUILD_DIR = $(GTEST_DIR)/build
GTEST_INCLUDE = -I$(GTEST_DIR)/googletest/include
GTEST_LIB = $(GTEST_BUILD_DIR)/lib/libgtest.a

SRC_DIR = app
TEST_DIR = app/test

SOURCES = $(wildcard $(SRC_DIR)/game/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

EXECUTABLE = quiz
TEST_EXECUTABLE = test_executable

all: $(EXECUTABLE) $(TEST_EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(SFML_LIBS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

run_tests: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_OBJECTS) 
	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o $(TEST_EXECUTABLE) $(GTEST_LIB) $(SFML_LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(SFML_INCLUDE) $(GTEST_INCLUDE) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(TEST_EXECUTABLE) $(TEST_OBJECTS)

format: 
	clang-format -i  $(SOURCES) $(TEST_SOURCES)
