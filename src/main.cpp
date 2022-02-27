#include<iostream>
#include<cassert>
#include<vector>
#include<cstdint>
#include<bitset>
#include<algorithm>
#include<cmath>
#include<memory>

#include "Cell.h"
#include "Board.h"

int main() {
	unsigned short temp;
	std::cin >> temp;
	const unsigned short GRID_SIZE = temp;
	const unsigned short sqrtGRID_SIZE = std::round(std::sqrt(GRID_SIZE));
	assert( sqrtGRID_SIZE*sqrtGRID_SIZE == GRID_SIZE );
	std::string inputBoard;
	std::cin >> inputBoard;

	Board initialBoard(inputBoard);
	
	return 0;
}