#include "Cell.h"
#include <cassert>
#include <cstdint>

Cell::Cell(std::uint8_t n){
    value = n;
    if(value == 0) 
        this->possibilities.set(); // 0 => all are possibilities 1,2,3,... 
    
    // if we have a value we can forget the bitset.
}

void Cell::init(std::uint8_t n){
    value = n;
    if (value == 0)
        possibilities.set();
}

bool Cell::isPossibility(std::uint8_t n) const {
    assert(1 <= n && n <= GRID_SIZE);
    return possibilities[n - 1];
}

void Cell::setPossibility(std::uint8_t n, bool val){
    assert(1 <= n && n <= GRID_SIZE);
    possibilities.set(n-1, val);
}

std::uint8_t Cell::getValue() const {
    return this->value;
}

void Cell::setValue(std::uint8_t n){
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
    for (unsigned int i = this->getValue() + 1; i <= GRID_SIZE; i++){
        if(isPossibility(i)){
            value = i;
            break;
        }
    }
}