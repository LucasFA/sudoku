#ifndef CELL_H
#define CELL_H

#include<bitset>

class Cell {
public:
    Cell(std::uint8_t n = 0);
    
    bool isPossibility(std::uint8_t n) const;
    void setPossibility(std::uint8_t n, bool val = false);

    std::uint8_t getValue() const;
    void setValue(std::uint8_t n = 0);
    void updateGivenNeighbouringCell(const Cell &other);

    std::uint8_t updateValue();

    void setNextPossibleValue();
private:
    std::uint8_t value;
    std::bitset<GRID_SIZE> possibilities; 
    // possibilities[i - 1] holds whether i is a possible value for the cell
};

#endif