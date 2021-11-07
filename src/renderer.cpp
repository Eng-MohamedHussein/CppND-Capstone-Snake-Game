#include "renderer.h"
#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  

  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  
  //Render the player details
  SDL_Rect PlayerStatics;
  
  PlayerStatics.w = screen_width;
  PlayerStatics.h = 75;
  PlayerStatics.x = 0;
  PlayerStatics.y = 0;
 /* SDL_RenderDrawRect(sdl_renderer,&PlayerStatics);
  SDL_SetRenderDrawColor(sdl_renderer, 138, 43, 226, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &PlayerStatics);*/

  SDL_Surface *Displayname = SDL_LoadBMP("../snake-1.bmp");
  if (nullptr == Displayname) {
    std::cerr << "Surface could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, Displayname);
  if (nullptr == texture) {
    std::cerr << "Texture could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  //TTF
  if(TTF_Init=-1)
  {
    std::cerr << "TTF could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }
  TTF_Font* Font1=TTF_OpenFont("../BodoniFLF-Roman.ttf",32)
  if(nullptr==Font1)
  {
    std::cerr << "font1 could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  SDL_Surface* surface2=TTF_RenderText_Solid(Font1,"Player name",{255,255,255});
  SDL_Texture* texture2=SDL_CreateTextureFromSurface(sdl_renderer,surface2);
  //Render a Texture 
  SDL_RenderCopy(sdl_renderer,texture2,NULL,&PlayerStatics);
  
  //Free resources
  SDL_FreeSurface(Displayname);
  SDL_DestroyTexture(texture);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
