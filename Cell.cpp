#include "Variables.h"
#include "Cell.h"

Cell::Cell(int value)
: value(value) { }

int Cell::getValue() const {
    return value;
}

void Cell::setValue(int value) {
    this->value = value;
}

bool Cell::isEmpty() {
    return (value == EMPTY);
}