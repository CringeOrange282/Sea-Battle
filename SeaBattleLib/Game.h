#pragma once
#include <iostream>
#include <sstream>
#include <cctype>
#include <string>
#include "Player.h"
class Game {
    Player _user;
    Player _computer;

    void user_init(std::string str);
    void computer_init(std::string str);

    State user_move(std::string input);
    void computer_move();

    bool is_end();
    std::string show_game_window();
public:
    Game();
    void start();
};


