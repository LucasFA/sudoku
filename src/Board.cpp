#include "Board.hpp"
#include "auxiliaryFunctions.hpp"

#include <vector>
#include <cassert>
#include <cmath>

Board::Board(const std::string &newBoard){
    std::vector<std::string> tempBoard( aux_functions::split(newBoard, ' ') );
    
    assert(tempBoard.size() == GRID_SIZE);

    for(std::size_t i = 0; i < GRID_SIZE; ++i){
        assert (tempBoard[i].size() == GRID_SIZE);

        for(std::size_t j = 0; j < GRID_SIZE; ++j){
            std::uint8_t temp = tempBoard[i][j] - '0';
            assert(0 <=temp && temp <= GRID_SIZE);
            board[i][j].init(temp);
        }
    }
    SQRT_GRID_SIZE = std::round(std::sqrt(GRID_SIZE));
    assert(SQRT_GRID_SIZE*SQRT_GRID_SIZE == GRID_SIZE);
}


void Board::solve(){
    /*
    Apply deduction rules.
    Apply backtracking over possibilities.
    */
    updateAll();
    deduction();
}

void Board::updateAll(){
    //Discovers impossibility values to depopulate in cells
    //TODO: do I really need to know whether it changed?
    bool somethingChanged = false;
    for (std::uint8_t i = 0; i < GRID_SIZE; i++){
        for (std::uint8_t j = 0; j < GRID_SIZE; j++){
            somethingChanged =  updateNeighbours(i, j) || somethingChanged;
        }
    }
}
void Board::deduction(){
    
}

bool Board::updateNeighbours(std::uint8_t p, std::uint8_t q){
    //TODO: performance improvement: iterator over the neighbourhood
    // Reason: eliminates a significant part of the repetition on the box - column/row overlap 
    // TODO: actually return value somethingCHanged
    bool somethingChanged = false;

    // Necessary check?
    if(this->board[p][q].getValue() == 0) return somethingChanged;
    
    //row
    for(std::size_t j = 0; j < GRID_SIZE; ++j){
        somethingChanged = board[p][j].setPossibility(board[p][q].getValue(), false) || somethingChanged;
    }
    
    // box
    unsigned short startingXCoordinateOfBox = p - (p % SQRT_GRID_SIZE);
    unsigned short startingYCoordinateOfBox = q - (q % SQRT_GRID_SIZE);
    for (unsigned short i = startingYCoordinateOfBox; i < startingYCoordinateOfBox + SQRT_GRID_SIZE; i++)
    {
        for (unsigned short j = startingXCoordinateOfBox; j < startingXCoordinateOfBox + SQRT_GRID_SIZE; j++)
        {
            somethingChanged = board[i][j].setPossibility(board[p][q].getValue(), false) || somethingChanged;
        }
    }
    //column
    for (std::size_t i = 0; i < GRID_SIZE; i++)
    {
        somethingChanged = board[i][q].setPossibility(board[p][q].getValue(), false) || somethingChanged;
    }
    return somethingChanged;
}
