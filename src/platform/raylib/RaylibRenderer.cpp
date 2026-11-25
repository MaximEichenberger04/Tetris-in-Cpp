#include "RaylibRenderer.h"
#include "../../core/Game.h"
#include "raylib.h"
#include <string>

namespace {
    // Grid coordinates are cells; raylib coordinates are pixels.
    constexpr int cellSize = 32;
    constexpr int boardX = 320;
    constexpr int boardY = 20;

    Color cellColor(Cell cell) {
        switch (cell) {
            case Cell::I: return SKYBLUE;
            case Cell::O: return YELLOW;
            case Cell::T: return PURPLE;
            case Cell::S: return GREEN;
            case Cell::Z: return RED;
            case Cell::J: return BLUE;
            case Cell::L: return ORANGE;
            case Cell::Empty: return Color{35, 38, 48, 255};
        }
        return WHITE;
    }

    Color pieceColor(TetrominoType type) {
        switch (type) {
            case TetrominoType::I: return cellColor(Cell::I);
            case TetrominoType::O: return cellColor(Cell::O);
            case TetrominoType::T: return cellColor(Cell::T);
            case TetrominoType::S: return cellColor(Cell::S);
            case TetrominoType::Z: return cellColor(Cell::Z);
            case TetrominoType::J: return cellColor(Cell::J);
            case TetrominoType::L: return cellColor(Cell::L);
        }
        return WHITE;
    }

    void drawCell(int x, int y, Color color) {
        // A small gap makes adjacent blocks distinguishable.
        DrawRectangle(boardX + x * cellSize + 1,
                      boardY + y * cellSize + 1,
                      cellSize - 2, cellSize - 2, color);
    }
}

void RaylibRenderer::render(const Game& game) {
    BeginDrawing();
    ClearBackground(Color{20, 22, 30, 255});

    // First draw the board, including its empty cells.
    const Board& board = game.board();
    for (std::size_t y = 0; y < board.height(); ++y) {
        for (std::size_t x = 0; x < board.width(); ++x) {
            drawCell(static_cast<int>(x), static_cast<int>(y),
                     cellColor(board.cells().at(x, y)));
        }
    }

    // The falling piece is separate from the settled board: overlay it.
    if (game.status() == GameStatus::Running) {
        const Piece& piece = game.activePiece();
        const Position position = piece.position();
        for (std::size_t y = 0; y < piece.shape().height(); ++y) {
            for (std::size_t x = 0; x < piece.shape().width(); ++x) {
                if (piece.shape().at(x, y)) {
                    drawCell(position.x + static_cast<int>(x),
                             position.y + static_cast<int>(y),
                             pieceColor(piece.type()));
                }
            }
        }
    }

    DrawRectangleLines(boardX - 1, boardY - 1,
                       static_cast<int>(board.width()) * cellSize + 2,
                       static_cast<int>(board.height()) * cellSize + 2, GRAY);
    const int textX = boardX + static_cast<int>(board.width()) * cellSize + 40;
    DrawText("TETRIS", textX, boardY, 36, RAYWHITE);
    const std::string scoreText = "Score: " + std::to_string(game.score());
    DrawText(scoreText.c_str(), textX, boardY + 60, 24, RAYWHITE);
    DrawText("A / D or arrows: move\nW / Up: rotate\nS / Down: soft drop\nSpace: hard drop\nQ / Escape: quit",
             textX, boardY + 120, 20, LIGHTGRAY);
    if (game.status() == GameStatus::GameOver) {
        DrawText("GAME OVER", textX, boardY + 300, 30, RED);
        DrawText("Press Q to exit", textX, boardY + 345, 20, LIGHTGRAY);
    }

    // Presents the frame and polls window/keyboard events for the next loop.
    EndDrawing();
}
