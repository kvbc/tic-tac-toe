#pragma once
#include <iostream>

typedef unsigned char uchar;

struct Player {
	uchar symbol;
	int wins = 0;
};

std::ostream& operator<< (std::ostream& out, const Player &p) {
	return out << p.symbol;
}