# include <SDL.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <stdbool.h>

# include "vectors.h"

# define WIDTH 1500
# define HEIGHT 800

# define SCALE 0.00003 // taille d'un m en px
# define ISS_MASS 450000
# define EARTH_RADIUS 6371000

void drawObject(SDL_Renderer * renderer, int x, int y) {
	SDL_Rect r1 = {x-1, y-3, 2, 6};
	SDL_Rect r2 = {x-3, y-1, 6, 2};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &r1);
	SDL_RenderFillRect(renderer, &r2);
}


int main(int argc, char **argv) {
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Surface * earth_surface;
	SDL_Texture * earth_texture;
	SDL_Texture * background_texture;
	struct timespec duration = {0, 40000000};

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
	
	background_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
	earth_texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("dessin-de-la-terre.bmp"));
	SDL_Rect earth_dest = {WIDTH/2-EARTH_RADIUS*SCALE, HEIGHT/2-EARTH_RADIUS*SCALE, EARTH_RADIUS*SCALE*2, EARTH_RADIUS*SCALE*2};
	
	SDL_SetRenderTarget(renderer, background_texture);
		SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(renderer, 0, HEIGHT/2, WIDTH, HEIGHT/2);
		SDL_RenderDrawLine(renderer, WIDTH/2, 0, WIDTH/2, HEIGHT);
		SDL_RenderCopy(renderer, earth_texture, NULL, &earth_dest);
	SDL_SetRenderTarget(renderer, NULL);

	struct PhysicalObject Earth = {{0, 0}, {0, 0}, 5.972e24};
	struct PhysicalObject ISS = {{6750000, 0}, {0, 7777},  ISS_MASS};  // Actual speed ist about 7777 m/s
	struct Vector a;
	SDL_Event event;
	while (true) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return EXIT_SUCCESS;
			}
		}
		a = get_acceleration_vector(&Earth, &ISS);
		
		ISS.movement = add(&ISS.movement, &a);
		ISS.pos.x += ISS.movement.x;
		ISS.pos.y += ISS.movement.y;
		SDL_RenderCopy(renderer, background_texture, NULL, NULL);
		drawObject(renderer, WIDTH/2+ISS.pos.x*SCALE, HEIGHT/2+ISS.pos.y*SCALE);
		SDL_RenderPresent(renderer);
	}
}
