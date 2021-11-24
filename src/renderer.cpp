#include "renderer.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "SDL.h"
#include "SDL2/SDL_ttf.h"


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
                                SDL_WINDOWPOS_CENTERED,screen_width,
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

void Renderer::Render(Snake const snake, SDL_Point const &food, Player const &ply) {
  SDL_Rect block;
  
  

  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  //black screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  // Clear the screen
  SDL_RenderClear(sdl_renderer);
  
  RenderPlayerStatics(ply);
  RenderLeader(ply);


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

//Render the player details feld
void Renderer::RenderPlayerStatics(Player ply)
{
  
    SDL_Rect PlayerData_1;
    SDL_Rect PlayerData_2;
    std::string playerName= "Player Name \t" + ply.GetName();
    std::string playerscore= "player score \t"+ std::to_string(ply.GetScore());

     
    //TTF intialization and using to draw text to the screen
    if(TTF_Init()==-1)
    {
        std::cerr << "TTF could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    //loading the required font template
    TTF_Font* Font1=TTF_OpenFont("../include/assets/MontereyFLF.ttf",16);
    if(nullptr==Font1)
    {
        std::cerr << "font1 could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }
    
    //intiating color for the text
    SDL_Color color2= {255,255,255,0};

    //ceating Surface to hold the text
    SDL_Surface* name_surface = TTF_RenderText_Solid(Font1,playerName.c_str(),color2);
    SDL_Surface* score_surface = TTF_RenderText_Solid(Font1,playerscore.c_str(),color2);
    if(nullptr==name_surface || nullptr == score_surface)
    {
        std::cerr << "name or score surface could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    //creating Texture to hold the text and to render to the surface
    SDL_Texture* name_texture = SDL_CreateTextureFromSurface(sdl_renderer,name_surface);
    SDL_Texture* score_texture = SDL_CreateTextureFromSurface(sdl_renderer,score_surface);
    if (nullptr == name_texture || nullptr == score_texture)
    {
      std::cerr << "Name or score Texture could not be created.\n";
      std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }
    //defining the text postion on the screen
    PlayerData_1.w = name_surface->w;
    PlayerData_1.h = name_surface->h;
    PlayerData_1.x =0;
    PlayerData_1.y =600;
    

    PlayerData_2.w = score_surface->w;
    PlayerData_2.h = score_surface->h;
    PlayerData_2.x =0;
    PlayerData_2.y =name_surface->h+PlayerData_1.y;

    
    
    //Render a Texture 
    SDL_RenderCopy(sdl_renderer,name_texture,NULL,&PlayerData_1);
    SDL_RenderCopy(sdl_renderer,score_texture,NULL,&PlayerData_2);
    
    
    
    //Free resources
    SDL_FreeSurface(name_surface);
    SDL_DestroyTexture(name_texture);
    TTF_Quit();
}


void Renderer::RenderLeader(Player ply)
{
  
    SDL_Rect PlayerData_1;
    SDL_Rect PlayerData_2;
    std::string playerName= "Leader \t" + ply.leadername;
    std::string playerscore= "score \t"+ std::to_string(ply.leaderscore);

     
    //TTF intialization and using to draw text to the screen
    if(TTF_Init()==-1)
    {
        std::cerr << "TTF could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    //loading the required font template
    TTF_Font* Font1=TTF_OpenFont("../include/assets/MontereyFLF.ttf",16);
    if(nullptr==Font1)
    {
        std::cerr << "font1 could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }
    
    //intiating color for the text
    SDL_Color color2= {55,255,55,0};

    //ceating Surface to hold the text
    SDL_Surface* name_surface = TTF_RenderText_Solid(Font1,playerName.c_str(),color2);
    SDL_Surface* score_surface = TTF_RenderText_Solid(Font1,playerscore.c_str(),color2);
    if(nullptr==name_surface || nullptr == score_surface)
    {
        std::cerr << "name or score surface could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    //creating Texture to hold the text and to render to the surface
    SDL_Texture* name_texture = SDL_CreateTextureFromSurface(sdl_renderer,name_surface);
    SDL_Texture* score_texture = SDL_CreateTextureFromSurface(sdl_renderer,score_surface);
    if (nullptr == name_texture || nullptr == score_texture)
    {
      std::cerr << "Name or score Texture could not be created.\n";
      std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }
    //defining the text postion on the screen
    PlayerData_1.w = name_surface->w;
    PlayerData_1.h = name_surface->h;
    PlayerData_1.x =320;
    PlayerData_1.y =600;
    

    PlayerData_2.w = score_surface->w;
    PlayerData_2.h = score_surface->h;
    PlayerData_2.x =320;
    PlayerData_2.y =name_surface->h+PlayerData_1.y;

    
    
    //Render a Texture 
    SDL_RenderCopy(sdl_renderer,name_texture,NULL,&PlayerData_1);
    SDL_RenderCopy(sdl_renderer,score_texture,NULL,&PlayerData_2);
    
    
    
    //Free resources
    SDL_FreeSurface(name_surface);
    SDL_DestroyTexture(name_texture);
    TTF_Quit();
}


std::string Renderer::RenderInputText( bool & running)
{
  
  //set drawing color for the next event / clear the screen and update the window
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  SDL_RenderPresent(sdl_renderer);

  
  

  //TTF intialization and using to draw text to the screen
  if(TTF_Init()==-1)
  {
      std::cerr << "TTF could not be created.\n";
      std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  //loading the required font template
  TTF_Font* Font1=TTF_OpenFont("../include/assets/MontereyFLF.ttf",22);
  if(nullptr==Font1)
  {
      std::cerr << "font1 could not be created.\n";
      std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }
  //intiating the font colors 
  SDL_Color color1= {255,255,255,0};
  SDL_Color color2= {255,128,2,0};

  //ceating Surface to hold the text
  SDL_Surface* input_surface= nullptr ;
  SDL_Surface* question_surface= nullptr ;
  
  //creating Texture to hold the text and to render to the surface
  SDL_Texture* input_texture = nullptr;
  SDL_Texture* question_texture = nullptr;

  question_surface = TTF_RenderText_Solid(Font1,"Please enter your name and then press Enter-Key",color1);
  question_texture = SDL_CreateTextureFromSurface(sdl_renderer,question_surface);
  if(nullptr==question_surface || nullptr== question_texture)
  {
      std::cerr << "question_surface or question_texture could not be created.\n";
      std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }
  //creating the space to display the question
  SDL_Rect questionRect;
  questionRect.w=question_surface->w;
  questionRect.h=question_surface->h;
  questionRect.x= (screen_width-question_surface->w )/2;
  questionRect.y= (screen_height/2);
  
  
  //drwaing the question to the screen
  SDL_RenderCopy(sdl_renderer,question_texture,NULL,&questionRect);
  SDL_RenderPresent(sdl_renderer);
  

  //starting to get input from tha user and storing that

  SDL_StartTextInput();
  bool typing = true;
  std::string in="";
  
  while ( typing ) {
    SDL_Event Input;
    
    while ( SDL_PollEvent( &Input ) ) 
    {

      // giving the user the abailtiy to end the game before or in time of typing his /her name
      if(Input.type== SDL_QUIT )
      {
        typing=false;
        running=false;
        break;
      }
      
      //limiting the lengt of the player name
      else if ( Input.type == SDL_TEXTINPUT  &&in.length()<30 ) 
      {
        in += Input.text.text;
        in.erase(std::remove_if(in.begin(), in.end(), ::isspace),in.end());
        
        std::cout << " > " << in << std::endl;// **************************************************************should be deleted by relase
        //resetting the screen to update text
        SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(sdl_renderer);
      
      } else if ( Input.type == SDL_KEYDOWN && Input.key.keysym.sym == SDLK_BACKSPACE && in.size()) 
      {
        in.pop_back();
        std::cout << " > " << in << std::endl;// **************************************************************should be deleted by relase
        
        //resetting the screen to update deleted text
        SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(sdl_renderer);

      }
      // accepting the entered name of the player 
      else if ( Input.type == SDL_KEYDOWN && Input.key.keysym.sym ==SDLK_RETURN) 
      {
        
        //avoid breaking the loop without the updating the last event
        // rendering the player name to the screen with each letter typed in or deleted
        input_surface = TTF_RenderText_Solid(Font1,in.c_str(),color2);
        SDL_RenderCopy(sdl_renderer,question_texture,NULL,&questionRect);
        SDL_RenderPresent(sdl_renderer);
        //entering the game without a name -> the default name will be used then
        if (nullptr != input_surface)
        {
          SDL_Rect InputData_1;
          InputData_1.w =input_surface->w;
          InputData_1.h = input_surface->h;
          InputData_1.x =(screen_width - input_surface->w)/2;
          InputData_1.y =(questionRect.y + 2*input_surface->h);

          
          input_texture = SDL_CreateTextureFromSurface(sdl_renderer,input_surface);
          
          
          SDL_RenderCopy(sdl_renderer,input_texture,NULL,&InputData_1);
          SDL_RenderPresent(sdl_renderer);
          //ply.SetName(in);
        }
        //if the user deleted the whole player name before entering the game
        //else{in=player.name;}
        //ply.SetName(in);
        typing = false;
        break;
      }
      else 
      {
        //to avoid rendering empty texture in the first loop cycle
        continue;
      }
      
      
      // rendering the player name to the screen with each letter typed in or deleted
      input_surface = TTF_RenderText_Solid(Font1,in.c_str(),color2);
      SDL_RenderCopy(sdl_renderer,question_texture,NULL,&questionRect);
      SDL_RenderPresent(sdl_renderer);
      //entering the game without a name -> the default name will be used then
      if (nullptr != input_surface)
      {
        SDL_Rect InputData_1;
        InputData_1.w =input_surface->w;
        InputData_1.h = input_surface->h;
        InputData_1.x =(screen_width - input_surface->w)/2;
        InputData_1.y =(questionRect.y + 2*input_surface->h);

        
        input_texture = SDL_CreateTextureFromSurface(sdl_renderer,input_surface);
        
        
        SDL_RenderCopy(sdl_renderer,input_texture,NULL,&InputData_1);
        SDL_RenderPresent(sdl_renderer);
        //ply.SetName(in);
        
        
      }
    }
    
  }

  SDL_StopTextInput();
  //Free resources
  SDL_FreeSurface(input_surface);
  SDL_FreeSurface(question_surface);
  SDL_DestroyTexture(input_texture);
  SDL_DestroyTexture(question_texture);
  
  TTF_Quit();
  return in.c_str();




}