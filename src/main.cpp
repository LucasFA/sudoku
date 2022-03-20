#include<iostream>
#include<string>

#include "Board.hpp"
#include "config.h"

int main() {
	const std::string inputBoard = 
		"030005086 000407300 010080400 090001000 000000027 700000108 805102000 074500001 100700030";
	Board board(inputBoard); // defined in config.h
	
	return 0;
}