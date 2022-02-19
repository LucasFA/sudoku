#include <iostream>
#include<cassert>
#include<vector>
#include <cstdint>
#include<bitset>
#include<algorithm>
#include<cmath>
#include<memory>

//Config
const unsigned short GRID_SIZE = 9; // ie, a 9x9 grid, with sqrt(9) = 3 sized boxes
const std::string inputBoard = "030005086 000407300 010080400 090001000 000000027 700000108 805102000 074500001 100700030";
//endConfig

constexpr unsigned short sqrtGRID_SIZE = static_cast<const unsigned short>( std::round(std::sqrt(GRID_SIZE)) );
static_assert( sqrtGRID_SIZE*sqrtGRID_SIZE == GRID_SIZE );

//helper for importing string into board type
std::vector<std::string> split(const std::string &s, const char splitterChar){
    std:vector<std::string> sol;
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
            //TODO: iterator over the neighbourhood
            // Reason: performance: eliminates a significant part of the repetition on the box - column/row overlap 
            bool somethingChanged = false;
            //iterates over neighbourhood

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

class Cell {
    public:
        Cell(unsigned short n = 0){
            value = n;
            if(value == 0) possibilities.set(); // 0 => all are possibilities 1,2,3,... 
            else possibilities.reset();         // if we have a value we could get rid of the bitset.
        }
        bool isPossibility(int n){
            assert(1 <= n && n <= GRID_SIZE);
            return possibilities[n - 1];
        }
        void setPossibility(int n, bool val = false){
            assert(1 <= n && n <= GRID_SIZE);
            possibilities.set(n-1, val);
        }
        unsigned short getValue(){
            return value;
        }
        void updateGivenNeighbouringCell(const Cell &other){
            if (other.getValue() != 0){
                this->setPossibility(other.getValue(), false);
            }
        }
        char updateValue(){
            if (value != 0){
                return 0;
            }
            unsigned char counter = 0;
            int positionOfSetBit = 0;
            for (size_t i = 0; i < possibilities.size(); i++)
            {
                if( !possibilities[i]){
                    counter++;
                    positionOfSetBit = i;
                }
            }
            if(counter > 1){
                return 0;
            }
            if(counter == 0){
                return -1;
                // Incompatible setup
            }
            //success: counter == 1
            value = positionOfSetBit + 1;
            return 1;
        }

        void setNextPossibleValue(){
            // FIXME: what's n
            for (size_t i = n + 1; i <= GRID_SIZE; i++)
            {
                if(isPossibility(i)){
                    value = i;
                    break;
                }
            }
            
        }
    private:
        unsigned char value; //integer of 1 byte
        std::bitset<GRID_SIZE> possibilities; 
        // possibilities[i - 1] holds whether i is a possible value for the cell
        //(only one value? => real value
};

int main() {
	Board initialBoard(inputBoard);
	
	return 0;
}