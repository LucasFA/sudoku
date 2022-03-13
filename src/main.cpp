#include<iostream>
#include<string>

#include "Board.h"
#include "config.h"

int main() {
	std::string inputBoard;
	std::cin >> inputBoard;

	Board board(inputBoard);
	
	return 0;
}