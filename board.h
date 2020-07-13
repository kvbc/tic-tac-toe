#pragma once
#include <iostream>
#define LEFT_MARGIN std::cout << "          ";

typedef unsigned char uchar;

class Board {
public:
	Board(uchar p1 = 'X', uchar p2 = 'O')
		: m_p1(p1),
		  m_p2(p2),
		  m_data{'1', '2', '3',
				 '4', '5', '6',
				 '7', '8', '9'} {}

	uchar* begin() {
		return m_data;
	}

	uchar* end() {
		return m_data + 9;
	}

	bool at(uchar *pos, uchar p) const;
	bool setpos(int pos, uchar p);
	bool is_full();
	bool has_won(uchar p);
	void print() const;

private:
	uchar m_p1;
	uchar m_p2;
	uchar m_data[9];
};


// When the index is out of bound return false,
// otherwise returns true if the value at that index is
// equal to the given value 'p'
bool Board::at(uchar *pos, uchar p) const {
	char diff = pos - m_data;
	if (
		diff < 0 ||
		diff >= 9
	)
		return false;
	return *pos == p;
}


// Sets the value at the given index to 'p'
// The given index is one-based
bool Board::setpos(int pos, uchar p) {
	if (
		pos < 1 ||
		pos > 9
	)
		return false;
	m_data[pos - 1] = p;
	return true;
}


// If the board is full returns true,
// otherwise returns false
bool Board::is_full() {
	for(uchar c : m_data)
		if(c >= '1' && c <= '9')
			return false;
	return true;
}


// Checks if the player 'p' has won in any of these three ways:
// - Vertically,
// - Horizontally,
// - Diagonally
bool Board::has_won(uchar p) {
	for (int i = 0; i < 9; i += 3) {
		uchar *_p = m_data + i;
		// Vertical check
		if (
			*_p == p	  &&
			at(_p + 1, p) &&
			at(_p + 2, p)
		)
			return true;
		// Diagonal check
		if (
			*_p == p	    && (
			(at(_p - 4, p)  &&
			 at(_p - 2, p)) ||
			(at(_p + 8, p)  &&
			 at(_p + 4, p)))
		)
			return true;
		// Horizontal check
		_p = m_data + 3 + i / 3;
		if (
			*_p == p	  &&
			at(_p - 3, p) &&
			at(_p + 3, p)
		)
			return true;
	}
	return false;
}


// Prints the board in the following way:
// (including the left margin)
/*
 ___________
/___________\
| p | p | p |
| p | p | p |
| p | p | p |
\___________/
*/
void Board::print() const {
	LEFT_MARGIN
	std::cout << " ___________ \n";
	LEFT_MARGIN
	std::cout << "/___________\\\n";
	for(int i = 0; i < 3; i++) {
		LEFT_MARGIN
		for(int j = 0; j < 3; j++) {
			uchar p = m_data[i * 3 + j];
			std::cout << "| " << p << ' ';
			if(j == 2)
				std::cout << '|';
		}
		std::cout << '\n';
	}
	LEFT_MARGIN
	std::cout << "\\___________/\n\n";
}