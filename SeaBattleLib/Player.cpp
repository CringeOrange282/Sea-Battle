#include "Player.h"

const int Player::_max_ships_counts[4] = { 4, 3, 2, 1 };

Player::Player() : _gamefield(), _ships_counts{ 0, 0, 0, 0 } {}

void Player::set_ship(const Ship& ship) {
    if (ship.size() < 1 || ship.size() > 4) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    if (_ships_counts[ship.size() - 1] >= _max_ships_counts[ship.size() - 1]) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    _gamefield.set(ship);
    _ships_counts[ship.size() - 1]++;
}

State Player::set_action(int row, char col) {
    State result = _gamefield.set(row, col);
    if (result == BoatDestroyed) { _ships_counts[0]--; }
    else if (result == DestroyersDestroyed) { _ships_counts[1]--; }
    else if (result == CruisersDestroyed) { _ships_counts[2]--; }
    else if (result == BattleshipDestroyed) { _ships_counts[3]--; }
    return result;
}

void Player::show_field(bool hide_ships) {
    std::cout << to_string(_gamefield, hide_ships);
    std::cout << "\nShips Left:\n" << "* - " << _ships_counts[0] << " ** - " << _ships_counts[1] << " *** - " << _ships_counts[2] << " **** - " << _ships_counts[3];
}

bool Player::check_lose() const {
    bool is_lose = true;
    for (int i = 0; i < 4; i++) {
        if (_ships_counts[i] != 0) {
            is_lose = false;
        }
    }
    return is_lose;
}

bool Player::check_ready() const {
    bool is_ready = true;
    for (int i = 0; i < 4; i++) {
        if (_ships_counts[i] != _max_ships_counts[i]) {
            is_ready = false;
        }
    }
    return is_ready;
}