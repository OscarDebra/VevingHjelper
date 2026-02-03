RAYLIB = external/raylib/src/libraylib.a

run: $(RAYLIB)
	g++ src/main.cpp -I external/raylib/src -L external/raylib/src -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -o project && ./project && rm ./project

$(RAYLIB):
	cd external/raylib/src && make PLATFORM=PLATFORM_DESKTOP

clean:
	rm -f project

test:
	clang++ -std=c++17 -I. tests/test.cpp -o tests/test && ./tests/test