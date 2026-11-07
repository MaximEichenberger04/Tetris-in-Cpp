#pragma once

#include "Piece.h"
#include "Types.h"
#include "Board.h"
#include "PieceGenerator.h"



class Game {
public:
    Game(); // Creates the board, generator, and first falling piece.

    const Board& board() const;
    const Piece& activePiece() const;
    int score() const;
    GameStatus status() const;

    // Return true when the proposed change is accepted.
    bool tryMove(int dx, int dy);
    bool tryRotate();
    // True: moved down. False: locked and spawned, or game already over.
    bool stepDown();

private:
    Board board_;
    PieceGenerator generator_;
    Piece activePiece_;
    int score_ = 0;
    GameStatus status_ = GameStatus::Running;

    void spawnPiece();
    void lockActivePiece();
};
