#pragma once

#include "Grid.h"
#include "Types.h"

class Piece {
public:
    explicit Piece(TetrominoType type);

    TetrominoType type() const;
    Position position() const;
    const Grid<bool>& shape() const;

    void setPosition(Position position);
    void move(int dx, int dy);
    void rotateClockwise();

private:
    TetrominoType type_;
    Position position_;
    Grid<bool> shape_;
};