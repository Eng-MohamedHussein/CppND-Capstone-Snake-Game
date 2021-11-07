#include "player.h"
#include "string"
#include "iostream"
#include "renderer.h"
#include "SDL.h"

/*Player::player()=default;
Player::~player() =default;*/

void Player::GetName()
{
   std::string name="";
   SDL_StartTextInput();
   SDL_Event event;
   while (SDL_PollEvent(&event))
   {
       if (event.type == SDL_QUIT) 
       {
            std::cerr << "Erorr in player.\n";
        }
      else if (event.type == SDL_TEXTINPUT) 
      {
          name += event.text.text;
      }
   }
   SDL_StopTextInput();

}

void Player::DisplayName()
{
 
  

  
}