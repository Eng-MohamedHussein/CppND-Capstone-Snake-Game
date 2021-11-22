#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "player.h"
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
void Player::UpdateLeaderBoard ()
{
    std::string line;
    std::string key;
    std::string OldName;
    int value;
    int OldValue;
    std::vector<std::string> ExistedNames;
    std::vector<int> ExistedScores;
    //bool exist =false;

    std::ifstream stream("../include/assets/LeaderBoard.txt");
    if(stream.is_open())
    {
        while(std::getline(stream, line))
        {
            std::istringstream stringstream(line);
            stringstream>>key>>value;
            std::cout<<key<<"\t"<<value<<std::endl;
            if(key==name)
            {
                OldName=key;
                OldValue=value;
                std::cout<<"Old name ist  ->"<<OldName<<std::endl;
            }
            else
            {
                ExistedNames.push_back(key);
                ExistedScores.push_back(value);
            }
            
        }
    }
    if(OldValue < score)
    {
        ExistedNames.push_back(OldName);
        ExistedScores.push_back(score);

        //override the LeaderBoard
        std::ofstream LeaderBoard("../include/assets/LeaderBoard.txt",std::ios::out);
    
        if(LeaderBoard.is_open())
        {
            for (auto i=0; i<ExistedNames.size();++i)
            {
                LeaderBoard<<ExistedNames[i]<<" "<< ExistedScores[i] <<std::endl;
                
            }
            
        }
        LeaderBoard.close();
    }

    /*std::ifstream stream("../include/assets/LeaderBoard.txt");
    if(stream.is_open())
    {
        while(std::getline(stream,line))
        {
            std::istringstream stringstream(line);
            stringstream>>key>>value;
            ExistedNames.emplace_back(key);
        }
    }
    for (auto i :ExistedNames)
    {
        if(name==i)
        {
            exist=true;
        }
    }
    if (!exist)
    {
        std::ofstream LeaderBoard("../include/assets/LeaderBoard.txt",std::ios::app);
    
        if(LeaderBoard.is_open())
        {
            LeaderBoard<<name<<" "<< score <<std::endl;
            LeaderBoard.close();
        }
    } */   
}
void Player::ReadLeadBoard()
{
    std::vector<int> scores;
    std::string key;
    std::string line;
    int value;
    std::ifstream stream("../include/assets/LeaderBoard.txt");
    if(stream.is_open())
    {
        while(std::getline(stream,line))
        {
            std::istringstream linestream(line);
            linestream>>key>>value;
            scores.emplace_back(value);
        }
    }
    leaderscore= *max_element(scores.begin(),scores.end());
    std::ifstream stream2("../include/assets/LeaderBoard.txt");
    if(stream2.is_open())
    {
        while(std::getline(stream2,line))
        {
            std::istringstream stringstream(line);
            stringstream>>key>>value;
            if(value==leaderscore)
            {
                leadername=key;
            }
        }
    }
}
