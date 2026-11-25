#include "TerminalRenderer.h"
#include "../../core/Game.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

TerminalRenderer::TerminalRenderer() {
    outputHandle_ = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleMode(outputHandle_, &originalMode_)) {
        throw std::runtime_error("Run Tetris directly in a Windows terminal, without output redirection.");
    }
    if (!SetConsoleMode(outputHandle_, originalMode_ | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
        throw std::runtime_error("This terminal does not support ANSI screen updates.");
    }
    // Switch to an alternate screen and hide the cursor.
    std::cout << "\x1b[?1049h\x1b[2J\x1b[H\x1b[?25l" << std::flush;
}

TerminalRenderer::~TerminalRenderer() {
    std::cout << "\x1b[0m\x1b[?25h\x1b[?1049l" << std::flush;
    SetConsoleMode(outputHandle_, originalMode_);
}

void TerminalRenderer::render(const Game& game) {
    const Board& board = game.board();
    const Piece& piece = game.activePiece();
    const Position position = piece.position();
    std::ostringstream frame;
    frame << "\x1b[H"; // Return to the top instead of scrolling each frame.
    frame << "TETRIS    Score: " << game.score() << "\x1b[K\n";
    frame << "A/D or arrows: move | W/Up: rotate\x1b[K\n";
    frame << "S/Down: drop | Space: hard drop | Q/Esc: quit\x1b[K\n";
    const std::string border = "+" + std::string(board.width() * 2, '-') + "+";
    frame << border << "\x1b[K\n";
    for (std::size_t y = 0; y < board.height(); ++y) {
        frame << '|';
        for (std::size_t x = 0; x < board.width(); ++x) {
            bool falling = false;
            const int localX = static_cast<int>(x) - position.x;
            const int localY = static_cast<int>(y) - position.y;
            if (game.status() == GameStatus::Running && localX >= 0 && localY >= 0
                && static_cast<std::size_t>(localX) < piece.shape().width()
                && static_cast<std::size_t>(localY) < piece.shape().height()) {
                falling = piece.shape().at(localX, localY);
            }
            if (falling) {
                frame << "\x1b[96m[]\x1b[0m";
            } else if (board.cells().at(x, y) != Cell::Empty) {
                frame << "[]";
            } else {
                frame << "  ";
            }
        }
        frame << "|\x1b[K\n";
    }
    frame << border << "\x1b[K\n";
    frame << (game.status() == GameStatus::GameOver
        ? "GAME OVER - press Q to exit."
        : "Clear full rows to earn 100 points each.");
    frame << "\x1b[K";
    std::cout << frame.str() << std::flush;
}
