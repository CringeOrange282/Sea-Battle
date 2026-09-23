#pragma once
#include <iostream>
#include <sstream>
#include <cctype>

enum Direction { Horizontal, Vertical };

class Position {
    int _row;
    int _col;
    static const int _max_row;
    static const int _max_col;

public:
    Position();
    Position(int row, int col);
    Position(const Position& other);
    Position(std::string str);
    Position(int, char);
    void row(int row);
    void col(int col);
    void col(char col);
    int row() const noexcept;
    int col() const noexcept;
    char char_col() const noexcept;
    friend void parse(const std::string&, Position&);
    friend bool is_collision(int);
    friend bool is_collision(char);
};

