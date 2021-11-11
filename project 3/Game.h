#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>

class Game
{
private:
    std::string name;
    int highScore;
    std::string initials;
    int plays;

public:
    Game(){name="", highScore=0, initials="", plays=0;}   //default constructor
    Game(std::string, int, std::string, int);   //overloaded constructor

    std::string getName(){return name;}
    int getHighScore(){return highScore;}
    std::string getInitials(){return initials;}
    int getPlays(){return plays;}

    void setName(std::string newName){name=newName;}
    void setScore(int newScore){highScore=newScore;}
    void setInitials(std::string newName){initials=newName;}
    void setPlays(int newPlays){plays=newPlays;}

    bool operator< (Game&);
    bool operator> (Game&);
    bool operator== (Game&);

    friend std::ostream& operator<< (std::ostream&, Game&);
};


#endif