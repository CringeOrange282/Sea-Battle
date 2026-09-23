#include "Game.h"

Game::Game(): _user(Player()), _computer(Player()) {}
void Game::user_init(std::string str) {
	std::stringstream ss(str);
	int row; char col; char direction; int size;
	while (ss >> size >> direction >> row >> col) {
		Ship ship = Ship(size, direction, row, col);
		_user.set_ship(ship);
	}
}

void Game::computer_init(std::string str) {
	std::stringstream ss(str);
	int row; char col; char direction; int size;
	while (ss >> size >> direction >> row >> col) {
		Ship ship = Ship(size, direction, row, col);
		_computer.set_ship(ship);
	}
}
State Game::user_move(std::string input) {
	int row; char col;
	std::stringstream ss(input);
	if (ss >> row >> col) {
		return _computer.set_action(row, col);
	}
	throw std::logic_error("Invalid input: incorrect move");
}

State Game::computer_move() {

	int row; char col;
}
