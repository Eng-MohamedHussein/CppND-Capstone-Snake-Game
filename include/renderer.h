#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "SDL2/SDL_ttf.h"
#include "player.h"

class Renderer 
{
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, Player const &ply);
  void UpdateWindowTitle(int score, int fps);
  void RenderPlayerStatics(Player ply);
  void RenderLeader(Player ply);
  std::string RenderInputText( bool & running);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif