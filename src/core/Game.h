#pragma once

#include "Piece.h"
#include "Types.h"
#include "Board.h"
#include "PieceGenerator.h"



class Game {
public:
    explicit Game(const GameSettings& settings = GameSettings{});

    const Board& board() const;
    const Piece& activePiece() const;
    int score() const;
    GameStatus status() const;

    // Return true when the proposed change is accepted.
    bool tryMove(int dx, int dy);
    bool tryRotate();
    // True: moved down. False: locked and spawned, or game already over.
    bool stepDown();
    
    void handleAction(Action action);
    // deltaTime is elapsed time in seconds; invalid/non-positive values are ignored.
    void update(double deltaTime);

private:
    Board board_;
    PieceGenerator generator_;
    Piece activePiece_;
    int score_ = 0;
    GameStatus status_ = GameStatus::Running;

    void spawnPiece();
    void lockActivePiece();

    double fallTimer_ = 0.0;
    double fallInterval_ = 0.5;
};
