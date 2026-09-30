#include "Game.h"
#include <random>
#include <sstream>
#include <iostream>

std::string state_to_string(State state) {
	switch (state) {
	case 0: return "Missed!";
	case 1: return "Hit!";
	case 2: return "Boat Destroyed!";
	case 3: return "Destroyer Destroyed!";
	case 4: return "Cruiser Destroyed!";
	case 5: return "Battleship Destroyed!";
	default: return "Unknown state!";
	}
}


Game::Game() : _user(Player()), _computer(Player()) {}

void Game::user_init(std::string str) {
	Ship ship = Ship(str);
	_user.set_ship(ship);
}
void Game::computer_init() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> randRow(1, 10);
	std::uniform_int_distribution<int> randCol(0, 9);
	std::uniform_int_distribution<int> randDir(0, 1);
	std::uniform_int_distribution<int> randSize(1, 4);

	while (!_computer.check_ready()) {
		int size = randSize(gen);
		int row = randRow(gen);
		int numb_col = randCol(gen);
		char col = 'A' + numb_col;
		char direction = (randDir(gen) == 0) ? 'H' : 'V';

		try {
			Ship ship = Ship(size, direction, row, col);
			_computer.set_ship(ship);
		}
		catch (const std::logic_error&) {
		}
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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> randRow(1, 10);
	std::uniform_int_distribution<int> randCol(0, 9);

	while (true) {
		int row = randRow(gen);
		int numb_col = randCol(gen);
		char col = 'A' + numb_col;
		try {
			return _user.set_action(row, col);
		}
		catch (const std::logic_error&) {
		}
	}
}

bool Game::is_end() {
	if (_user.check_lose()) {
		std::cout << "You lose\n";
		return true;
	}
	else if (_computer.check_lose()) {
		std::cout << "You win\n";
		return true;
	}
	return false;
}

void Game::show_game_window() {
	system("cls");
	std::cout << "= COMPUTER GAME FIELD =\n";
	_computer.show_field(false);
	std::cout << "\n=== YOUR PLAY FIELD ===\n";
	_user.show_field(true);
	std::cout << "\n";
}

void Game::start() {
	std::string input;

	std::cout << "=== SEA BATTLE: PLACING SHIPS ===\n";
	std::cout << "Enter ships (format: size direction row col), '4 H 1 A':\n";

	while (!_user.check_ready() && std::getline(std::cin, input)) {
		try {
			user_init(input);
			show_game_window();
		}
		catch (const std::logic_error&) {
			std::cout << "Invalid ship placement! Try again.\n";
		}
	}

	computer_init();
	std::cin.clear();
	show_game_window();

	while (true) {
		std::cout << "Your turn (format: row col), '5 E': ";

		if (!std::getline(std::cin, input)) break;

		try {
			State status = user_move(input);
			show_game_window();
			std::cout << "Shot result: " << state_to_string(status) << "\n";
			std::cout << "\nPress Enter to see Computer's move...";
			std::string Enter;
			std::getline(std::cin, Enter);

			if (is_end()) {
				break;
			}

			std::cout << "\nComputer is making a move...\n";
			computer_move();
			show_game_window();

			if (is_end()) {
				break;
			}
		}
		catch (const std::logic_error&) {
			std::cout << "Invalid move! Try again.\n";
		}
	}
}