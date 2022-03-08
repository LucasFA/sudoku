#include "Cell.h"
#include <cassert>
#include <cstdint>
Cell::Cell(std::uint8_t n = 0){
    value = n;
    if(value == 0) 
        this->possibilities.set(); // 0 => all are possibilities 1,2,3,... 
    else 
        this->possibilities.reset();         // if we have a value we could get rid of the bitset.
}

bool Cell::isPossibility(std::uint8_t n) const {
    assert(1 <= n && n <= possibilities.size());
    return possibilities[n - 1];
}

void Cell::setPossibility(std::uint8_t n, bool val = false){
    assert(1 <= n && n <= possibilities.size());
    possibilities[n-1] = val;
}

std::uint8_t Cell::getValue() const {
    return this->value;
}
void Cell::setValue(std::uint8_t n = 0){
    this->value = n;
}
void Cell::updateGivenNeighbouringCell(const Cell &other){
    if (other.getValue() != 0){
        this->setPossibility(other.getValue(), false);
    }
}
std::uint8_t Cell::updateValue(){
    if (value != 0){
        return 0;
    }
    std::uint8_t counter = 0;
    std::uint8_t positionOfSetBit = 0;
    for (std::size_t i = 0; i < possibilities.size(); i++)
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

void Cell::setNextPossibleValue(){
    for (unsigned int i = this->getValue() + 1; i <= possibilities.size(); i++){
        if(isPossibility(i)){
            value = i;
            break;
        }
    }
}