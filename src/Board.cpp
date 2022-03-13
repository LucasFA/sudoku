#include "Board.h"
#include<vector>
#include<cassert>
#include<cmath>

Board::Board(const std::string &newBoard){
    std::vector<std::string> tempBoard(split(newBoard, ' '));
    
    assert(tempBoard.size() == GRID_SIZE);

    for(std::size_t i = 0; i < GRID_SIZE; ++i){
        assert (tempBoard[i].size() == GRID_SIZE);

        for(std::size_t j = 0; j < GRID_SIZE; ++j){
            std::uint8_t temp = tempBoard[i][j];
            assert(0 <=temp && temp <= GRID_SIZE);
            board[i][j].init(temp);
        }
    }
    SQRT_GRID_SIZE = std::round(std::sqrt(GRID_SIZE));
    assert(SQRT_GRID_SIZE*SQRT_GRID_SIZE == GRID_SIZE);
}

//helper for importing string into board type
std::vector<std::string> Board::split(const std::string &s, const char splitterChar){
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
        sol.push_back(temp);
    return sol;
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
    for (std::size_t i = 0; i < GRID_SIZE; i++){
        for (std::size_t j = 0; j < GRID_SIZE; j++){
            // updateLegalMovesOfCell(i, j); // actually, just implement here
        }
    }
}

bool Board::updateNeighbours(std::size_t p, std::size_t q){
    //TODO: performance improvement: iterator over the neighbourhood
    // Reason: eliminates a significant part of the repetition on the box - column/row overlap 
    bool somethingChanged = false;

    if(this->board[p][q].getValue() == 0) return;
    
    //row
    for(std::size_t j = 0; j < GRID_SIZE; ++j){
        board[p][j].updateGivenNeighbouringCell(board[p][q]);
    }
    
    // box
    unsigned short startingXCoordinateOfBox = p - (p % SQRT_GRID_SIZE);
    unsigned short startingYCoordinateOfBox = q - (q % SQRT_GRID_SIZE);
    for (unsigned short i = startingYCoordinateOfBox; i < startingYCoordinateOfBox + SQRT_GRID_SIZE; i++)
    {
        for (unsigned short j = startingXCoordinateOfBox; j < startingXCoordinateOfBox + SQRT_GRID_SIZE; j++)
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
