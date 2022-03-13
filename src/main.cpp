#include<iostream>
#include<cassert>
#include<cstdint>
#include<cmath>
#include<string>

#include "Cell.h"
#include "Board.h"

int main() {
	std::string inputBoard;
	std::cin >> inputBoard;

	Board board(inputBoard);
	
	return 0;
}