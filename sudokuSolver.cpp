#include <iostream>
#include<cassert>
#include<vector>
#include <cstdint>
#include<bitset>
#include<algorithm>
#include<cmath>
#include<memory>

#include "Cell.h"
//TODO: put config in separate file, not in build
//Config
const unsigned short GRID_SIZE = 9; // ie, a 9x9 grid, with sqrt(9) = 3 sized boxes
const std::string inputBoard = "030005086 000407300 010080400 090001000 000000027 700000108 805102000 074500001 100700030";
//endConfig

//FIXME: turn static_assert into assert (take into account GRID_SIZE won't  be available at compiel time)
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

//TODO: modularise Board class into separate file
class Board {
	public:
        Board(const std::string &newBoard){
            const char space = " "[0];
            std::vector<std::string> tempBoard(split(newBoard, space));
            
            assert(tempBoard.size() == GRID_SIZE);

            for(std::size_t i = 0; i < GRID_SIZE; ++i){
                assert (tempBoard[i].size() == GRID_SIZE);
                for(std::size_t j = 0; j < GRID_SIZE; ++j){
                    board[i][j](static_cast<int>(tempBoard[i][j]));
                }
            }

        }

        void solve(){
            /*
            Apply deduction rules.
            Apply backtracking over possibilities.
            */
           solveInitialisation();
           

        }

	private:
        std::array<std::array<Cell, GRID_SIZE>, GRID_SIZE> board;
        
        void solveInitialisation(){
            //Discovers impossibility values to depopulate in cells
            for (std::size_t i = 0; i < GRID_SIZE; i++)
            {
                for (std::size_t j = 0; j < GRID_SIZE; j++)
                {
                    updateLegalMovesOfCell(i, j);
                }
            }
        }

        bool updateNeighbours(std::size_t p, std::size_t q){
            //TODO: performance improvement: iterator over the neighbourhood
            // Reason: eliminates a significant part of the repetition on the box - column/row overlap 
            bool somethingChanged = false;

            if(board[p][q].getvalue() == 0) return;
            
            //row
            for(std::size_t j = 0; j < GRID_SIZE; ++j){
                board[p][j].updateGivenNeighbouringCell(board[p][q]);
            }
            
            // box
            std::size_t startingXCoordinateOfBox = p - (p % sqrtGRID_SIZE);
            std::size_t startingYCoordinateOfBox = q - (q % sqrtGRID_SIZE);
            for (size_t i = startingYCoordinateOfBox; i < startingYCoordinateOfBox + sqrtGRID_SIZE; i++)
            {
                for (size_t j = startingXCoordinateOfBox; j < startingXCoordinateOfBox + sqrtGRID_SIZE; j++)
                {
                    board[i][j].updateGivenNeighbouringCell(board[p][q]);
                }
            }
            //column
            for (std::size_t i = 0; i < GRID_SIZE; i++)
            {
                board[i][q].updateGivenNeighbouringCell(board[p][q]);
            }
        }


// NOTE: Board grows quadratically on input board size: GRID_SIZE*GRID_SIZE cells, the size of the input board, times each taking GRID_SIZE bits
// quadratically on GRID_SIZE: linearly on the number of cells and the cells linearly themselves on GRID_SIZE
// Not really a concern for small boards, but for GRID_SIZE = 100, 100*100 cells of size 100 (128) bits = 16 bytes is ~160 KB, potentially tanking performance
};



int main() {
	Board initialBoard(inputBoard);
	
	return 0;
}