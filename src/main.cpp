#include <iostream>
#include <thread>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "player.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Player player;
  //starting a thread to read the Leader Board and join at the end of the game
  std::thread FindTheLeader  (&Player::ReadLeadBoard,&player);
  //player.ReadLeadBoard();
  //test// std::cout << "Leader is " << player.leadername << "\n";
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer,player, kMsPerFrame);
  //joining the thread before ending the main thread
  FindTheLeader.join();


  //updating the leader board
  player.UpdateLeaderBoard();
  
  
  /*std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";*/
  return 0;
}