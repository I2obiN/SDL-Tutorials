// www.willusher.io / lazyfoot.net
// SDL Tutorials

#include <iostream>
#include <string>
#include <SDL.h>

// Create a new Win32 window var
SDL_Window *win = SDL_CreateWindow("Hello World", 100, 100, 640, 480, SDL_WINDOW_OPENGL);

// Render Window var
SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

// Event Handler for all SDL events, keyboard strokes, mouse clicks, etc
SDL_Event e;

// Load image
SDL_Surface *bmp = SDL_LoadBMP("hello.bmp");

	// Load an image as a texture onto a surface object
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);

void close() {
	// Clean up & Exit
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void init() {
	// Check SDL Video
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL Not Initialized! : " << SDL_GetError() << std::endl;
	}

	// Check if window generated
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error : " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	// Check if render generated
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		std::cout << "Error Rendering: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	// Check if image loaded
	if (bmp == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "404 Error Loading picture: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	if (tex == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "Texture Error 404 : " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

}

	// Rendering loop -- now event driven
int main(int argc, char **argv) {
	// Main loop flag
	bool quit = false;
		
	while (!quit) {
		// SDL_PollEvent continues polling SDL_Event
		while (SDL_PollEvent(&e) != 0) {
			// Check if user has quit
			if(e.type == SDL_QUIT)
			{ quit = true; }

			// Else proceed with program ..

			// Clear Renderer
			SDL_RenderClear(ren);
			// Copy the texture into the renderer
			SDL_RenderCopy(ren, tex, NULL, NULL);
			// Render 
			SDL_RenderPresent(ren);
			// Delay to see picture
			SDL_Delay(1000);
		}
	}
	
	close();
	return 1;
}
