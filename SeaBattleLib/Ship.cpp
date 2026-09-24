#include "Ship.h"

bool is_collision(int size, Position position, Direction direction) {
        if (size < 1 || size > 4) {
            return true;
        }
    if (position.row() < 1 || position.row() > 10 || position.col() < 1 || position.col() > 10) {
        return true;
    }
    if (direction == Horizontal) {
        if (position.col() + size - 1 > 10) {
            return true;
        }
    }
    else if (direction == Vertical) {
        if (position.row() + size - 1 > 10) {
            return true;
        }
    }
    return false;
}

void parse(const std::string& str, Ship& other) {
    std::stringstream stream(str);
    int size;
    char dir;
    int row;
    char col;

    if (!(stream >> size >> dir >> row >> col)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }

    Direction direction;
    if (dir == 'H' || dir == 'h') {
        direction = Horizontal;
    }
    else if (dir == 'V' || dir == 'v') {
        direction = Vertical;
    }
    else {
        throw std::logic_error("Invalid input: incorrect ship");
    }

    Position position(row, col);

    if (is_collision(size, position, direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }

    other._size = size;
    other._direction = direction;
    other._position = position;
}

Ship::Ship(int size, Position position, Direction direction) {
    if (is_collision(size, position, direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _size = size;
    _position = position;
    _direction = direction;
}

Ship::Ship(int size, char direction, int row, char col) {
    Direction dir;
    if (direction == 'H' || direction == 'h') {
        dir = Horizontal;
    }
    else if (direction == 'V' || direction == 'v') {
        dir = Vertical;
    }
    else {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    Position pos(row, col);
    if (is_collision(size, pos, dir)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _size = size;
    _position = pos;
    _direction = dir;
}

Ship::Ship(std::string str) {
    parse(str, *this);
}

int Ship::size() const noexcept { return _size; }
int Ship::row() const noexcept { return _position.row(); }
int Ship::col() const noexcept { return _position.col(); }
Position Ship::position() const noexcept { return _position; }
Direction Ship::direction() const noexcept { return _direction; }

void Ship::size(int size) {
    if (is_collision(size, _position, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _size = size;
}

void Ship::row(int row) {
    Position pos(row, _position.col());
    if (is_collision(_size, pos, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = pos;
}

void Ship::col(int col) {
    Position pos(_position.row(), col);
    if (is_collision(_size, pos, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = pos;
}

void Ship::col(char col) {
    Position pos(_position.row(), col);
    if (is_collision(_size, pos, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = pos;
}

void Ship::direction(Direction direction) {
    if (is_collision(_size, _position, direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _direction = direction;
}

void Ship::direction(char direction) {
    Direction dir;
    if (direction == 'H' || direction == 'h') {
        dir = Horizontal;
    }
    else if (direction == 'V' || direction == 'v') {
        dir = Vertical;
    }
    else {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    if (is_collision(_size, _position, dir)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _direction = dir;
}

void Ship::position(Position position) {
    if (is_collision(_size, position, _direction)) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
    _position = position;
}