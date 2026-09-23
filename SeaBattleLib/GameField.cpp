#include "GameField.h"

bool is_collision(const GameField& gf, const Ship& ship) {
    int min_row = ship.position().row() - 1;
    int min_col = ship.position().col() - 1;
    int max_row = min_row;
    int max_col = min_col;

    if (ship.direction() == Horizontal) {
        max_col = min_col + ship.size() - 1;
    }
    else if (ship.direction() == Vertical) {
        max_row = min_row + ship.size() - 1;
    }

    int start_r = std::max(0, min_row - 1);
    int end_r = std::min(gf._n - 1, max_row + 1);
    int start_c = std::max(0, min_col - 1);
    int end_c = std::min(gf._m - 1, max_col + 1);

    for (int r = start_r; r <= end_r; ++r) {
        for (int c = start_c; c <= end_c; ++c) {
            if (gf._field[r][c] == '*') {
                return true;
            }
        }
    }
    return false;
}

int GameField::check_destroy(int row, int col) {
    int ship_size = 1;
    bool has_alive_parts = false;

    int c = col - 1;
    while (c >= 0 && (_field[row][c] == 'X' || _field[row][c] == '*')) {
        if (_field[row][c] == '*') {
            has_alive_parts = true;
        }
        ship_size++;
        c--;
    }

    c = col + 1;
    while (c < _m && (_field[row][c] == 'X' || _field[row][c] == '*')) {
        if (_field[row][c] == '*') {
            has_alive_parts = true;
        }
        ship_size++;
        c++;
    }

    int r = row - 1;
    while (r >= 0 && (_field[r][col] == 'X' || _field[r][col] == '*')) {
        if (_field[r][col] == '*') {
            has_alive_parts = true;
        }
        ship_size++;
        r--;
    }

    r = row + 1;
    while (r < _n && (_field[r][col] == 'X' || _field[r][col] == '*')) {
        if (_field[r][col] == '*') {
            has_alive_parts = true;
        }
        ship_size++;
        r++;
    }

    if (has_alive_parts) {
        return 0;
    }

    return ship_size;
}

GameField::GameField() : _n(10), _m(10) {
    if (_n < 1 || _n > 25 || _m < 1 || _m > 25) {
        throw std::logic_error("Invalid input: incorrect field parameters");
    }
    _field = new char* [_n];
    for (int i = 0; i < _n; i++) {
        _field[i] = new char[_m];
        for (int j = 0; j < _m; j++) {
            _field[i][j] = ' ';
        }
    }
}

GameField::~GameField() {
    for (int i = 0; i < _n; i++) {
        delete[] _field[i];
    }
    delete[] _field;
    _field = nullptr;
}

State GameField::set(int n, char m) {
    int numb_m = m - 'A';
    if (n < 1 || n > _n || numb_m < 0 || numb_m >= _m) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    if (_field[n - 1][numb_m] == ' ') {
        _field[n - 1][numb_m] = '.';
        return Missed;
    }
    else if (_field[n - 1][numb_m] == '*') {
        _field[n - 1][numb_m] = 'X';
        int checking = check_destroy(n - 1, numb_m);
        if (checking == 0) {
            return Hit;
        }
        else if (checking == 1) {
            return BoatDestroyed;
        }
        else if (checking == 2) {
            return DestroyersDestroyed;
        }
        else if (checking == 3) {
            return CruisersDestroyed;
        }
        else if (checking == 4) {
            return BattleshipDestroyed;
        }
    }
    throw std::logic_error("Invalid input: incorrect move");
}

void GameField::set(const Ship& ship) {
    int start_row = ship.position().row() - 1;
    int start_col = ship.position().col() - 1;

    if (start_row < 0 || start_row >= _n || start_col < 0 || start_col >= _m) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    if (ship.direction() == Horizontal && start_col + ship.size() > _m) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    if (ship.direction() == Vertical && start_row + ship.size() > _n) {
        throw std::logic_error("Invalid input: incorrect field");
    }

    if (is_collision(*this, ship)) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    for (int i = 0; i < ship.size(); i++) {
        if (ship.direction() == Horizontal) {
            _field[start_row][start_col + i] = '*';
        }
        else if (ship.direction() == Vertical) {
            _field[start_row + i][start_col] = '*';
        }
    }
}

char GameField::get(int n, char m) const {
    int numb_m = m - 'A';
    if (n < 1 || n > _n || numb_m < 0 || numb_m >= _m) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    return _field[n - 1][numb_m];
}

std::string to_string(const GameField& gf, bool show_ships) {
    std::string res = "";

    res += "  |";
    for (int j = 0; j < gf._m; ++j) {
        res += (char)('A' + j);
        if (j < gf._m - 1) {
            res += " ";
        }
    }
    res += "|\n";

    res += "  +";
    for (int j = 0; j < gf._m * 2 - 1; ++j) {
        res += "-";
    }
    res += "+\n";

    for (int i = 0; i < gf._n; ++i) {
        if (i + 1 < 10) {
            res += std::to_string(i + 1) + " |";
        }
        else {
            res += std::to_string(i + 1) + "|";
        }

        for (int j = 0; j < gf._m; ++j) {
            char cell = gf._field[i][j];
            if (cell == '*' && !show_ships) {
                res += ' ';
            }
            else {
                res += cell;
            }
            if (j < gf._m - 1) {
                res += "|";
            }
        }
        res += "|\n";
    }

    res += "  +";
    for (int j = 0; j < gf._m * 2 - 1; ++j) {
        res += "-";
    }
    res += "+\n";

    return res;
}