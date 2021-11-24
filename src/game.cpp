#include <iostream>
#include <string>
#include "game.h"
#include "SDL.h"
#include "player.h"



Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height-2),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 8)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer, Player &player,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  
  std::string temp =renderer.RenderInputText(running);
  if (temp.size()>0)
  {
    player.SetName(temp);
  }
  /*SDL_Delay(2000);
  std::cout<<"the player name is "<<player_object.GetName()<<std::endl;
  std::cout<<"the player score is "<<player_object.GetScore()<<std::endl;*/
  

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update(player);
    //std::cout<<"the player score is "<<player_object.GetScore()<<std::endl;
    renderer.Render(snake, food, player);
    //renderer.RenderPlayer(player_object);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update(Player &ply) {
  if (!snake.alive) return;

  snake.Update();
  ply.SetScore(score);

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }