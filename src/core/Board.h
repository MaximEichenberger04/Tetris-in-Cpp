#pragma once

#include <cstddef>
#include "Grid.h"
#include "Piece.h"
#include "Types.h"

class Board {
public:
    Board(std::size_t width = 10, std::size_t height = 20);

    std::size_t width() const;
    std::size_t height() const;
    const Grid<Cell>& cells() const;

    bool canPlace(const Piece& piece) const;
    void lockPiece(const Piece& piece);
    int clearFullRows();

private:
    Grid<Cell> cells_;
    static Cell cellForType(TetrominoType type);
};
