# include <SDL.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include "vectors.h"

# define WIDTH 800
# define HEIGHT 500

# define SCALE 0.00005 // taille d'un m en px
# define ISS_MASS 450000

void drawObject(SDL_Renderer * renderer, int x, int y) {
	SDL_Rect r1 = {x-4, y-10, 8, 20};
	SDL_Rect r2 = {x-10, y-4, 20, 8};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &r1);
	SDL_RenderFillRect(renderer, &r2);
	SDL_RenderPresent(renderer);
}


int main(int argc, char **argv) {
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Surface * earth_surface;
	SDL_Texture * earth_texture;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Init failed\n");
		return EXIT_FAILURE;
	}
	
	window = SDL_CreateWindow("Modélisations physique", SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

	if (window == NULL) {
		fprintf(stderr, "Error while creating the window\n");
		return EXIT_FAILURE;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		fprintf(stderr, "Error while creating the renderer\n");
		return EXIT_FAILURE;
	}
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, 0, HEIGHT/2, WIDTH, HEIGHT/2);
	SDL_RenderDrawLine(renderer, WIDTH/2, 0, WIDTH/2, HEIGHT);
	SDL_RenderPresent(renderer);

	earth_texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("dessin-de-la-terre.bmp"));

	SDL_Rect dest = {WIDTH/2-50, HEIGHT/2-50, 100, 100};
	SDL_RenderCopy(renderer, earth_texture, NULL, &dest);

//	drawObject(renderer, WIDTH/2+6750*SCALE, HEIGHT/2);
	SDL_RenderPresent(renderer);
	
	struct PhysicalObject Earth = {{0, 0}, {0, 0}, 5.972e24};
	struct PhysicalObject ISS = {{6750000, 0}, {0, 0},  ISS_MASS};
	SDL_Event event;
	while (true) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return EXIT_SUCCESS;
			}
		}
		struct Vector a = get_acceleration_vector(&Earth, &ISS);
		printf("Accélération causée par la terre : x = %lf, y = %lf\n", a.x, a.y);
		printf("Position de l'ISS : x = %lf, y = %lf\n", ISS.pos.x, ISS.pos.y);
		printf("Mouvement de l'ISS : x = %lf, y = %lf\n\n", ISS.movement.x, ISS.movement.y);
//		SDL_Delay(5);
		ISS.movement = add(&ISS.movement, &a);
		ISS.pos.x += ISS.movement.x;
		ISS.pos.y += ISS.movement.y;
//		if (ISS.pos.x < 6371000) return 0;
		drawObject(renderer, WIDTH/2+ISS.pos.x*SCALE, HEIGHT/2+ISS.pos.y);
		SDL_RenderPresent(renderer);
		if (ISS.pos.x < 0) return 0;
	}
}
