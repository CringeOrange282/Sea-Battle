#include "Position.h"

int to_integer(char ch) {
    int numb_ch;
    if (std::isupper(ch)) {
        numb_ch = ch - 'A' + 1;
    }
    else {
        numb_ch = ch - 'a' + 1;
    }
    return numb_ch;
}

bool is_collision(int row) {
        return (row < 1 || row > Position::_max_row);
}

bool is_collision(char col) {
    int numb_col = to_integer(col);
    return (numb_col < 1 || numb_col > Position::_max_col);
}

void parse(const std::string& str, Position& other) {
    int row; char col;
    std::stringstream stream(str);
    if (!(stream >> row >> col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    if (is_collision(row) || is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    int numb_col = to_integer(col);

    other._row = row;
    other._col = numb_col;
}

Position::Position() {
    _row = rand() % 10 + 1;
    _col = rand() % 10 + 1;
}
Position::Position(int row, int col) {
    if (is_collision(row) || col < 1 || col > Position::_max_col) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    else {
        _row = row;
        _col = col;
    }
}
Position::Position(const Position& other) {
    _row = other._row;
    _col = other._col;
}
Position::Position(std::string str) {
    parse(str, *this);
}
Position::Position(int row, char col) {
    if (is_collision(row) || is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    else {
        _row = row;
        _col = std::isupper(col) ? (col - 'A' + 1) : (col - 'a' + 1);
    }
}
void Position::set_row(int row) {
    if (is_collision(row)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    else {
        _row = row;
    }
}
void Position::set_col(int col) {
    if (col < 1 || col > _max_col) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    else {
        _col = col;
    }
}
void Position::set_col(char col) {
    if (is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    else {
        _col = to_integer(col);
    }
}
int Position::get_row() const noexcept { return _row; }
int Position::get_col() const noexcept { return _col; }

char Position::get_char_col() const noexcept {
    return 'A' + _col - 1;
}

const int Position::_max_row = 10;
const int Position::_max_col = 10;