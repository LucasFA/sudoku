#ifndef CELL_H
#define CELL_H
class Cell {
public:
    Cell(unsigned short n = 0);
    
    bool isPossibility(int n);
    void setPossibility(int n, bool val = false);

    unsigned short getValue();

    void updateGivenNeighbouringCell(const Cell &other);

    std::uint_8 updateValue();

    void setNextPossibleValue();
private:
    std::uint_8 value;
    std::bitset<GRID_SIZE> possibilities; 
    // possibilities[i - 1] holds whether i is a possible value for the cell
};

#endif