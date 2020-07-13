#pragma once
#include <string>
#include "board.h"
#include "player.h"

#define ERR_INVALID_INPUT -1
#define ERR_FULL_SLOT 0


class Game {
public:
	Game(Player &p1, Player &p2)
		: m_p1(p1),
		  m_p2(p2) {
			m_running = true;
			system("cls");
			m_board.print();
		}

	void exit();
	bool running();
	int getpos();
	void handle_turn(Player &p);

private:
	bool m_running;
	Player &m_p1;
	Player &m_p2;
	Board m_board;
};


// Function that gets executed when 
// the user wants to exit the program
void Game::exit() {
	std::cout << '\n';
	std::cout << m_p1 << "'s wins: " << m_p1.wins << '\n';
	std::cout << m_p2 << "'s wins: " << m_p2.wins << "\n\n";
	system("pause");
}


// Returns an boolean that tells us if the game is still running
bool Game::running() {
	return m_running;
}


// Gets the position to place the value at from the user,
// accepts only 1 character input between 1 and 9
int Game::getpos() {
	std::string line;
	std::getline(std::cin, line);

	if(line == "exit")
		this->exit();

	if(line.length() != 1)
		return ERR_INVALID_INPUT;

	int pos = line[0] - '0';
	if(pos < 1 || pos > 9)
		return ERR_INVALID_INPUT;

	uchar slot = *(m_board.begin() + pos - 1);
	if(slot < '1' || slot > '9')
		return ERR_FULL_SLOT;

	return pos;
}


// Function managing the whole game object while
// the player 'p' is making it's turn
void Game::handle_turn(Player &p) {
	// We don't want the player to make the turn
	// when the other player has just won
	if(!m_running) return;

	std::cout << p << "'s turn!\n";
	std::cout << "Enter a number corresponding to the position on the board (1-9)\nTo exit the program type 'exit'\n\n" << p << ": ";

	// While loop for getting user's valid input
	int pos = getpos();
	while(!m_board.setpos(pos, p.symbol)) {
		if(pos == ERR_INVALID_INPUT)
			std::cout << "\nInvalid input, try again!\n" << p << ": ";
		else if(pos == ERR_FULL_SLOT)
			std::cout << "\nThe slot is full!\n" << p << ": ";
		pos = getpos();
	}

	// Clear the console and print the updated board
	system("cls");
	m_board.print();

	// If the board is full (it's a tie)
	if(m_board.is_full()) {
		m_running = false;
		std::cout << "It's a tie!\n";
	}

	// In the case that player has won
	// stop the game and display a message
	else if(m_board.has_won(p.symbol)) {
		m_running = false;
		std::cout << p << " has won!\n";
		p.wins++;
	}
}
