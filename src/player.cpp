#include "player.h"
#include "string"
#include "iostream"
#include "renderer.h"
#include "SDL.h"
#include "SDL2/SDL_ttf.h"


Player::Player()
{
    name="Unknown";
    score= 0;
}
Player::~Player(){}

void Player::SetName (std::string playername) 
{
    name =playername;
} 
void Player::SetScore (int playerscore)
{
    score =playerscore;
}

std::string Player::GetName ()
{
    return name;
}

int Player::GetScore ()
{
    return score;
}
