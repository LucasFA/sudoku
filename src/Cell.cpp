#include "Cell.h"

Cell::Cell(unsigned short n = 0){
    value = n;
    if(value == 0) possibilities.set(); // 0 => all are possibilities 1,2,3,... 
    else possibilities.reset();         // if we have a value we could get rid of the bitset.
}

bool Cell::isPossibility(int n){
    assert(1 <= n && n <= GRID_SIZE);
    return possibilities[n - 1];
}

void Cell::setPossibility(int n, bool val = false){
    assert(1 <= n && n <= GRID_SIZE);
    possibilities.set(n-1, val);
}

std::uint_8 Cell::getValue(){
    return value;
}
Cell::updateGivenNeighbouringCell(const Cell &other){
    if (other.getValue() != 0){
        this->setPossibility(other.getValue(), false);
    }
}
std::int_8 Cell::updateValue(){
    if (value != 0){
        return 0;
    }
    std::uint_8 counter = 0;
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

Cell::setNextPossibleValue(){
    // FIXME: what's n
    for (size_t i = n + 1; i <= GRID_SIZE; i++)
    {
        if(isPossibility(i)){
            value = i;
            break;
        }
    }
    
}
