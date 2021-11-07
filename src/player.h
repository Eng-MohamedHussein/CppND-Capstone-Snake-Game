#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
private:
    std::string name;
    int score;

public:
    
    void GetName ();
    void GetScore ();
    void DisplayName();

    void SetName ();
    void SetScore ();
    void UpdateLeaderBoard ();

};

#endif