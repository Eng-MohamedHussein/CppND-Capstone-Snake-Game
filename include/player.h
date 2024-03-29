#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player 
{
private:
    std::string name ="Unknown";
    std::string const LeaderBoardPath="../include/assets/LeaderBoard.txt";
    int score;
    
    

public:
    Player();
    ~Player();
    std::string GetName ();
    int GetScore ();
    void DisplayName();

    void SetName (std::string playername);
    void SetScore (int score);
    void UpdateLeaderBoard ();
    void ReadLeadBoard();

    int leaderscore;
    std::string leadername;
    
};

#endif