all:
	clang++ -std=c++11 main.cpp `sdl-config --cflags --libs` -o main.out
run: all
	./main.out
clean:
	rm -rf ./main.out

