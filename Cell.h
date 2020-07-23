#ifndef CELL_H
#define CELL_H

class Cell {
    private:
        int value;
    public:
        Cell(int value);
        int getValue() const;
        void setValue(int value);
        bool isEmpty();
};

#endif
