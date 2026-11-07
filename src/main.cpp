#include <cstddef>
#include <iostream>

#include "core/Piece.h"
#include "core/Board.h"

void printBoard(const Board& board) {
    for (std::size_t y = 0; y < board.height(); ++y) {
        for (std::size_t x = 0; x < board.width(); ++x) {
            std::cout << (board.cells().at(x, y) != Cell::Empty ? '#' : '.');
        }
        std::cout << '\n';
    }
}

void printPiece(const Piece& piece) {
    const Grid<bool>& shape = piece.shape();

    for (std::size_t y = 0; y < shape.height(); ++y) {
        for (std::size_t x = 0; x < shape.width(); ++x) {
            std::cout << (shape.at(x, y) ? '#' : '.');
        }

        std::cout << '\n';
    }
}

int main() {
    Piece piece(TetrominoType::T);

    std::cout << "Original:\n";
    printPiece(piece);

    piece.rotateClockwise();

    std::cout << "\nRotated clockwise:\n";
    printPiece(piece);

    piece.setPosition({3, 0});
    piece.move(-1, 1);

    const Position position = piece.position();

    std::cout << "\nPosition: "
              << position.x << ", "
              << position.y << '\n';

    Board board(4, 6);
    Piece line(TetrominoType::I);
    // The horizontal I occupies local row 1, so this fills board row 5.
    line.setPosition({0, 4});

    std::cout << std::boolalpha;
    std::cout << "\nFits: " << board.canPlace(line) << '\n';
    board.lockPiece(line);

    std::cout << "\nBefore clearing:\n";
    printBoard(board);
    const int cleared = board.clearFullRows();
    std::cout << "\nRows cleared: " << cleared << '\n';
    printBoard(board);
}
