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

//TODO: put config in separate file, not in build #1
//Config
const unsigned short GRID_SIZE = 9; // ie, a 9x9 grid, with sqrt(9) = 3 sized boxes
const std::string inputBoard = "030005086 000407300 010080400 090001000 000000027 700000108 805102000 074500001 100700030";
//endConfig

//FIXME: turn static_assert into assert (take into account GRID_SIZE won't  be available at compile time) #1
constexpr unsigned short sqrtGRID_SIZE = static_cast<const unsigned short>( std::round(std::sqrt(GRID_SIZE)) );
static_assert( sqrtGRID_SIZE*sqrtGRID_SIZE == GRID_SIZE );

//helper for importing string into board type
std::vector<std::string> split(const std::string &s, const char splitterChar){
    std::vector<int> temp;
    std::vector<std::string> sol;
    std::size_t lastSubstringSectionStartsAt = 0;
    for(std::size_t i = 0; i < s.size(); ++i){
        if(s[i] == splitterChar) {
            sol.push_back(s.substr(lastSubstringSectionStartsAt, i - lastSubstringSectionStartsAt));
            lastSubstringSectionStartsAt = i + 1;
        }
    }
    std::string temp = s.substr(lastSubstringSectionStartsAt, s.size() - lastSubstringSectionStartsAt);
    if (!temp.empty()) 
        sol.push_back(std::move(temp));
    return sol;
}


int main() {
	Board initialBoard(inputBoard);
	
	return 0;
}