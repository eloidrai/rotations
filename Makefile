main: main.c vectors.c
	gcc -o $@ $^ `sdl2-config --libs --cflags` -lm
