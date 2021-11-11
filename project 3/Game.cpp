#include "Game.h"
#include <string>
#include <iostream>
#include <iomanip>

Game::Game(std::string nName, int nHighScore, std::string nInitials, int nPlays){
    name = nName;
    highScore = nHighScore;
    initials = nInitials;
    plays = nPlays;
}

bool Game::operator< (Game& rhs){
    if(name < rhs.name){
        return true;
    }
    return false;
}

bool Game::operator> (Game& rhs){
    if(name > rhs.name){
        return true;
    }
    return false;
}

bool Game::operator== (Game& rhs){
    if(name == rhs.name || name.find(rhs.name)!=std::string::npos){
        return true;
    }
    return false;
}

std::ostream& operator<< (std::ostream& out, Game& rhs){
    out << std::fixed << std::setprecision(2);
    out << rhs.name << ", " << rhs.highScore << ", " << rhs.initials << ", " << rhs.plays << ", " << "$" <<(rhs.plays*.25);
    return out;
}