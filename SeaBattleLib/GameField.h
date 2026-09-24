#pragma once
#include <iostream>
#include <sstream>
#include <cctype>
#include <string>
#include "Ship.h"

enum State { Missed, BoatDestroyed, DestroyersDestroyed, CruisersDestroyed, BattleshipDestroyed, Hit };

class GameField;

bool is_collision(const GameField& gf, const Ship& ship);
std::string to_string(const GameField& gf, bool show_ships = true);

class GameField {
    char** _field;
    const int _n;
    const int _m;
public:
    GameField();
    ~GameField();

    State set(int n, char m);
    void set(const Ship& ship);
    char get(int n, char m) const;

    friend std::string to_string(const GameField& gf, bool show_ships);
    friend bool is_collision(const GameField& gf, const Ship& ship);

    int check_destroy(int, int);
};
