CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I include -I external/raylib/src
LDFLAGS  := -L external/raylib/src -lraylib \
            -framework OpenGL -framework Cocoa \
            -framework IOKit -framework CoreVideo

RAYLIB := external/raylib/src/libraylib.a

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)
CONFIG_SRC := src/config.cpp

TARGET := project


run: $(TARGET)
	./$(TARGET)

run-clean: $(TARGET)
	./$(TARGET)
	$(MAKE) clean


$(TARGET): $(OBJ) $(RAYLIB)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(TARGET)


src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(RAYLIB):
	cd external/raylib/src && make PLATFORM=PLATFORM_DESKTOP

clean:
	rm -f $(OBJ) $(TARGET)

test:
	clang++ -std=c++17 -I include tests/test.cpp -o tests/test && ./tests/test