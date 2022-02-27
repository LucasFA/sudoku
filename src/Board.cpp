#include "Board.h"
#include<vector>
#include<cassert>
Board::Board(const std::string &newBoard){
    const char space = ' ';
    std::vector<std::string> tempBoard(split(newBoard, space));
    
    assert(tempBoard.size() == GRID_SIZE);

    for(std::size_t i = 0; i < GRID_SIZE; ++i){
        assert (tempBoard[i].size() == GRID_SIZE);
        for(std::size_t j = 0; j < GRID_SIZE; ++j){
            board[i][j](static_cast<int>(tempBoard[i][j]));
        }
    }
}

void Board::solve(){
    /*
    Apply deduction rules.
    Apply backtracking over possibilities.
    */
    solveInitialisation();
    
}

void Board::solveInitialisation(){
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
