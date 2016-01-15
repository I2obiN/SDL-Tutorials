// http://www.willusher.io
// SDL Tutorials

#include <iostream>
#include <string>
#include <SDL.h>

int main(int argc, char **argv) {

	// Initializes SDL Video
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL Not Initialized! : " << SDL_GetError() << std::endl;
		return 1;
	}

	// Create a new Win32 window
	SDL_Window *win = SDL_CreateWindow("Hello World", 100, 100, 640, 480, SDL_WINDOW_OPENGL);

	// Check if window generated
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Render Window
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		std::cout << "Error Rendering: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Load our image/resource
	SDL_Surface *bmp = SDL_LoadBMP("hello.bmp");
	if (bmp == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "404 Error Loading picture: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Load an image as a texture onto a surface object
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "Texture Error 404 : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Rendering loop
	for (int i = 0; i < 3; i++) {
		// Clear Renderer
		SDL_RenderClear(ren);
		// Copy the texture into the renderer
		SDL_RenderCopy(ren, tex, NULL, NULL);
		// Render 
		SDL_RenderPresent(ren);
		// Delay to see picture
		SDL_Delay(1000);
	}

	// Clean up & Exit
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
