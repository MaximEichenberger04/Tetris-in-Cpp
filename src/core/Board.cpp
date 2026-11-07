#include "Board.h"

#include <stdexcept>

Board::Board(std::size_t width, std::size_t height)
    : cells_(width, height, Cell::Empty)
{
}

std::size_t Board::width() const {
    return cells_.width();
}

std::size_t Board::height() const {
    return cells_.height();
}

const Grid<Cell>& Board::cells() const {
    return cells_;
}

bool Board::canPlace(const Piece& piece) const {
    const Grid<bool>& shape = piece.shape();
    const Position position = piece.position();

    for (std::size_t y = 0; y < shape.height(); ++y) {
        for (std::size_t x = 0; x < shape.width(); ++x) {
            // Only occupied squares participate in collision checks.
            if (!shape.at(x, y)) {
                continue;
            }

            const long long boardX = static_cast<long long>(position.x)
                                   + static_cast<long long>(x);
            const long long boardY = static_cast<long long>(position.y)
                                   + static_cast<long long>(y);

            if (boardX < 0 || boardY < 0) {
                return false;
            }

            const auto column = static_cast<std::size_t>(boardX);
            const auto row = static_cast<std::size_t>(boardY);

            if (column >= width() || row >= height()) {
                return false;
            }

            if (cells_.at(column, row) != Cell::Empty) {
                return false;
            }
        }
    }

    return true;
}

void Board::lockPiece(const Piece& piece) {
    // Validate everything before writing any cells.
    if (!canPlace(piece)) {
        throw std::invalid_argument("Cannot lock a piece at an invalid position.");
    }

    const Grid<bool>& shape = piece.shape();
    const Position position = piece.position();
    const Cell value = cellForType(piece.type());

    for (std::size_t y = 0; y < shape.height(); ++y) {
        for (std::size_t x = 0; x < shape.width(); ++x) {
            if (!shape.at(x, y)) {
                continue;
            }

            const auto boardX = static_cast<std::size_t>(
                static_cast<long long>(position.x) + static_cast<long long>(x));
            const auto boardY = static_cast<std::size_t>(
                static_cast<long long>(position.y) + static_cast<long long>(y));

            cells_.at(boardX, boardY) = value;
        }
    }
}

int Board::clearFullRows() {
    int clearedRows = 0;
    std::size_t writeRow = height();

    // Scan upward, keeping non-full rows in their original order.
    for (std::size_t readRow = height(); readRow > 0;) {
        --readRow;
        bool full = true;

        for (std::size_t x = 0; x < width(); ++x) {
            if (cells_.at(x, readRow) == Cell::Empty) {
                full = false;
                break;
            }
        }

        if (full) {
            ++clearedRows;
            continue;
        }

        --writeRow;
        if (writeRow != readRow) {
            for (std::size_t x = 0; x < width(); ++x) {
                cells_.at(x, writeRow) = cells_.at(x, readRow);
            }
        }
    }

    // Empty the vacated rows at the top.
    for (std::size_t y = 0; y < writeRow; ++y) {
        for (std::size_t x = 0; x < width(); ++x) {
            cells_.at(x, y) = Cell::Empty;
        }
    }

    return clearedRows;
}

Cell Board::cellForType(TetrominoType type) {
    switch (type) {
        case TetrominoType::I: return Cell::I;
        case TetrominoType::O: return Cell::O;
        case TetrominoType::T: return Cell::T;
        case TetrominoType::S: return Cell::S;
        case TetrominoType::Z: return Cell::Z;
        case TetrominoType::J: return Cell::J;
        case TetrominoType::L: return Cell::L;
    }

    throw std::invalid_argument("Unknown tetromino type.");
}
