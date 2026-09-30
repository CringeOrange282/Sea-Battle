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
    void set_row(int row);
    void set_col(int col);
    void set_col(char col);
    int get_row() const noexcept;
    int get_col() const noexcept;
    char get_char_col() const noexcept;
    friend void parse(const std::string&, Position&);
    friend bool is_collision(int);
    friend bool is_collision(char);
};

int to_integer(char ch);