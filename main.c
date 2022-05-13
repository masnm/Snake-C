#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "cvector.h"

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 360;

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
		SDL_Rect rect = { .x = 0, .y = i, .w = 5, .h = 5 };
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
			default: {}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		//SDL_RenderDrawRects(SDL_Renderer * renderer, const SDL_Rect * rects, int count);
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderDrawRects ( renderer, cvector_data ( &snake ), (int)snake.size );
		// do render
		// end render
		SDL_RenderPresent(renderer);
	}

	cvector_destroy ( &snake );
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
