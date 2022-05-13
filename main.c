#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "cvector.h"

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
const int CELL_WIDTH = 12, CELL_HEIGHT = 9;

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window *window = SDL_CreateWindow("Snake-C",
										  100, 100,
										  SCREEN_WIDTH, SCREEN_HEIGHT,
										  SDL_WINDOW_SHOWN);

	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
												SDL_RENDERER_ACCELERATED |
												SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}


	// typedef struct SDL_Rect { int x, y; int w, h; } SDL_Rect;
	cvector snake = cvector_create ( sizeof(SDL_Rect) );
	for ( int i = 0 ; i < 10 ; ++i ) {
		SDL_Rect rect = { .x = i*CELL_WIDTH, .y = SCREEN_HEIGHT/CELL_HEIGHT, .w = CELL_WIDTH, .h = CELL_HEIGHT };
		cvector_emplace_back ( &snake, &rect );
	}

	bool done = false;
	SDL_Event e;
	while ( !done ) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				switch( e.key.keysym.sym ){
					case SDLK_LEFT:
						break;
					case SDLK_RIGHT:
						break;
					case SDLK_UP:
						break;
					case SDLK_DOWN:
						break;
					default:
						break;
				}
				break;
			default: {}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderDrawRects ( renderer, cvector_data ( &snake ), (int)cvector_size ( &snake ) );
		// do render
		// end render
		SDL_RenderPresent(renderer);
	}

	cvector_destroy ( &snake );
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
