#pragma once
#include <iostream>
#include <sstream>
#include <cctype>
#include <string>
#include "Player.h"

std::string state_to_string(State state);

class Game {
    Player _user;
    Player _computer;

    void user_init(std::string str);
    void computer_init();

    State user_move(std::string input);
    State computer_move();

    bool is_end();
    void show_game_window();
public:
    Game();
    void start();
};


