#include<iostream>
#include<string>

#include "Board.h"

int main() {
	std::string inputBoard;
	std::cin >> inputBoard;

	Board board(inputBoard);
	
	return 0;
}