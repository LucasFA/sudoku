#ifndef BOARD_H
#define BOARD_H

#include<string>
#include<array>
#include "Cell.h"

class Board {
public:
    Board(const std::string &newBoard);
    void solve();

private:
    std::array<std::array<Cell, GRID_SIZE>, GRID_SIZE> board;
    
    std::vector<std::string> Board::split(const std::string &s, const char splitterChar);
    void solveInitialisation();
    bool updateNeighbours(std::size_t p, std::size_t q);

// NOTE: Board grows quadratically on input board size: GRID_SIZE*GRID_SIZE cells, the size of the input board, times each taking GRID_SIZE bits
// quadratically on GRID_SIZE: linearly on the number of cells and the cells linearly themselves on GRID_SIZE
// Not really a concern for small boards, but for GRID_SIZE = 100, 100*100 cells of size 100 (128) bits = 16 bytes is ~160 KB, potentially tanking performance
};

#endif