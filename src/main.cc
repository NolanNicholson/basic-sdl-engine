#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface* loadPNG(const char* filepath, SDL_PixelFormat* format) {

  //Load the PNG (and check for errors)
  SDL_Surface *loaded_surface = IMG_Load(filepath);
  if (loaded_surface == NULL) {
    std::cerr << "Unable to load PNG " << filepath << ": "
      << IMG_GetError() << std::endl;
    throw "Failed to load PNG";
  }

  //Convert the surface to the screen format
  SDL_Surface *optimized_surface = SDL_ConvertSurface(
      loaded_surface, format, 0);
  SDL_FreeSurface(loaded_surface);

  //Check for successful optimization
  if (optimized_surface == NULL) {
    std::cerr << "Unable to optimize image " << filepath << ": "
      << SDL_GetError() << std::endl;
    throw "Failed to optimize PNG image";
  }

  return optimized_surface;
}

int main() {
  std::cout << "Starting SDL" << std::endl;

  int screen_width = 640;
  int screen_height = 480;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    throw "Failed to initialize SDL";
  }

  //Create window
  SDL_Window *window = NULL;
  window = SDL_CreateWindow("SDL Test",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      screen_width,
      screen_height,
      SDL_WINDOW_SHOWN
      );
  if (window == NULL) {
    std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
    throw "Failed to create window";
  }

  //Initialize SDL_image, for PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    std::cerr << "Could not init SDL_image: " << IMG_GetError() << std::endl;
    throw "Failed to initialize SDL_image";
  }

  //Get window surface
  SDL_Surface *screenSurface = NULL;
  screenSurface = SDL_GetWindowSurface(window);

  //Load PNG test resource
  SDL_Surface *test_img = loadPNG(
      "img/gba_mk_mario.png", screenSurface->format);

  //Fill surface with solid color
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(
        screenSurface->format, 0xFF, 0xFF, 0xFF));

  //Blit the test image to the screen
  SDL_BlitSurface(test_img, NULL, screenSurface, NULL);

  //Update surface
  SDL_UpdateWindowSurface(window);

  //Delay
  SDL_Delay(2000);

  //Destroy window and quit
  SDL_DestroyWindow(window);
  SDL_Quit();
}
