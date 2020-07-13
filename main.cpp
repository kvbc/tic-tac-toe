#include "game.h"

int main() {
	Player p1{'X'};
	Player p2{'O'};

start:
	Game game(p1, p2);

	// Game loop
	while(game.running()) {
		game.handle_turn(p1);
		if(!game.running())
			std::swap(p1, p2);
		else
			game.handle_turn(p2);
	}

	// Game ended, get if the user wants to continue
	std::string line;
	std::cout << "\nDo you want to continue?\ny/n: ";
	std::getline(std::cin, line);

	// While loop for getting user's valid input
	while (
		line.length() != 1 &&
		line[0] != 'y'	   &&
		line[0] != 'n'
	) {
		std::cout << "\nInvalid input, try again!\ny/n: ";
		std::getline(std::cin, line);
	}
	
	// Stop / Continue
	if(line[0] == 'n')
		game.exit();
	goto start;
}