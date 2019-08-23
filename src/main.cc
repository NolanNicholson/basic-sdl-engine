#include <iostream>
#include <SDL2/SDL.h>

int main() {
  std::cout << "Starting SDL" << std::endl;

  int screen_width = 640;
  int screen_height = 480;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    throw "Failed to initialize SDL";
  }

  //Create window
  SDL_Window* window = NULL;
  window = SDL_CreateWindow("SDL Test",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      screen_width,
      screen_height,
      SDL_WINDOW_SHOWN
      );
  if (window == NULL) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    throw "Failed to create window";
  }

  //Get window surface
  SDL_Surface* screenSurface = NULL;
  screenSurface = SDL_GetWindowSurface(window);

  //Fill surface with solid color
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(
        screenSurface->format, 0xFF, 0xFF, 0xFF));

  //Update surface
  SDL_UpdateWindowSurface(window);

  //Delay
  SDL_Delay(2000);
}
