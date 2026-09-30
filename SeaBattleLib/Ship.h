#pragma once
#include "Position.h"
#include <iostream>
#include <sstream>
#include <cctype>

class Ship {
    int _size;
    Position _position;
    Direction _direction;

public:
    Ship(int size, Position position, Direction direction);
    Ship(int size, char direction, int row, char col);
    Ship(std::string str);

    int size() const noexcept;
    int row() const noexcept;
    int col() const noexcept;
    Position position() const noexcept;
    Direction direction() const noexcept;

    void size(int size);
    void row(int row);
    void col(int col);
    void col(char col);
    void direction(Direction direction);
    void direction(char direction);
    void position(Position position);

    friend void parse(const std::string&, Ship&);
    friend bool is_collision(int, Position, Direction);

};