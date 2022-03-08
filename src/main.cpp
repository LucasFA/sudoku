#include<iostream>
#include<cassert>
#include<cstdint>
#include<cmath>
#include<string>

#include "Cell.h"
#include "Board.h"

int main() {
	unsigned short sudokuSize;
	std::cin >> sudokuSize;
	unsigned short sqrtGRID_SIZE = std::round(std::sqrt(sudokuSize));
	assert( sqrtGRID_SIZE*sqrtGRID_SIZE == sudokuSize );
	std::string inputBoard;
	std::cin >> inputBoard;

	Board Board(inputBoard, sudokuSize);
	
	return 0;
}