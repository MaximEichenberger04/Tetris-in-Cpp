#include "Piece.h"

#include <cstddef>
#include <stdexcept>
#include <utility>

Piece::Piece(TetrominoType type)
    : type_(type),
      position_{0, 0},
      shape_(4, 4, false)
{
    // Each string represents one row.
    // '#' is occupied; '.' is empty.
    const char* rows[4];

    switch (type_) {
        case TetrominoType::I: // I: straight line
            rows[0] = "....";
            rows[1] = "####";
            rows[2] = "....";
            rows[3] = "....";
            break;

        case TetrominoType::O: // O: square
            rows[0] = ".##.";
            rows[1] = ".##.";
            rows[2] = "....";
            rows[3] = "....";
            break;

        case TetrominoType::T: // T: T-shape
            rows[0] = ".#..";
            rows[1] = "###.";
            rows[2] = "....";
            rows[3] = "....";
            break;

        case TetrominoType::S: // S: Right-handed skew
            rows[0] = ".##.";
            rows[1] = "##..";
            rows[2] = "....";
            rows[3] = "....";
            break;

        case TetrominoType::Z: // Z: Left-handed skew
            rows[0] = "##..";
            rows[1] = ".##.";
            rows[2] = "....";
            rows[3] = "....";
            break;

        case TetrominoType::L: // L: L-shape
            rows[0] = "#...";
            rows[1] = "###.";
            rows[2] = "....";
            rows[3] = "....";
            break;

        case TetrominoType::J: // J: Mirrored L-shape
            rows[0] = "..#.";
            rows[1] = "###.";
            rows[2] = "....";
            rows[3] = "....";
            break;

        default:
            throw std::invalid_argument("Unknown tetromino type.");
    }

    for (std::size_t y = 0; y < shape_.height(); ++y) {
        for (std::size_t x = 0; x < shape_.width(); ++x) {
            shape_.at(x, y) = (rows[y][x] == '#');
        }
    }
}

TetrominoType Piece::type() const {
    return type_;
}

Position Piece::position() const {
    return position_;
}

const Grid<bool>& Piece::shape() const {
    return shape_;
}

void Piece::setPosition(Position position) {
    position_ = position;
}

void Piece::move(int dx, int dy) {
    position_.x += dx;
    position_.y += dy;
}

void Piece::rotateClockwise() {
    // Rotating the square should not change its appearance or position.
    if (type_ == TetrominoType::O) {
        return;
    }

    Grid<bool> rotated(4, 4, false);

    // The I piece rotates within a 4×4 area.
    // Other pieces rotate within the top-left 3×3 area.
    const std::size_t size =
        (type_ == TetrominoType::I) ? 4 : 3;

    for (std::size_t y = 0; y < size; ++y) {
        for (std::size_t x = 0; x < size; ++x) {
            rotated.at(size - 1 - y, x) = shape_.at(x, y);
        }
    }

    shape_ = std::move(rotated);
}