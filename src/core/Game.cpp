
#include "Game.h"

#include <utility>
#include <cmath>

Game::Game(const GameSettings& settings)
    : board_(10, 20),
      generator_(settings.randomizer),
      activePiece_(TetrominoType::I)
{
    switch (settings.difficulty) {
        case Difficulty::Easy: fallInterval_ = 0.8; break;
        case Difficulty::Medium: fallInterval_ = 0.5; break;
        case Difficulty::Hard: fallInterval_ = 0.25; break;
    }
    // Piece requires a type during construction. The temporary I above is
    // immediately replaced here; only spawnPiece draws from the random bag.
    spawnPiece();
}

const Board& Game::board() const {
    return board_;
}

const Piece& Game::activePiece() const {
    return activePiece_;
}

int Game::score() const {
    return score_;
}

GameStatus Game::status() const {
    return status_;
}

bool Game::tryMove(int dx, int dy) {
    if (status_ != GameStatus::Running) {
        return false;
    }

    // Try on a copy so a rejected movement leaves the real piece unchanged.
    Piece candidate = activePiece_;
    candidate.move(dx, dy);

    if (!board_.canPlace(candidate)) {
        return false;
    }

    activePiece_ = std::move(candidate);
    return true;
}

bool Game::tryRotate() {
    if (status_ != GameStatus::Running) {
        return false;
    }

    Piece candidate = activePiece_;
    candidate.rotateClockwise();

    if (!board_.canPlace(candidate)) {
        return false;
    }

    activePiece_ = std::move(candidate);
    return true;
}

void Game::spawnPiece() {
    if (status_ != GameStatus::Running) {
        return;
    }

    activePiece_ = Piece(generator_.next());

    const int spawnX = static_cast<int>(board_.width() / 2)
                     - static_cast<int>(activePiece_.shape().width() / 2);
    activePiece_.setPosition({spawnX, 0});
    // Each new piece gets a full interval before its first gravity step.
    fallTimer_ = 0.0;

    // If settled blocks occupy the new piece's spawn cells, play ends.
    if (!board_.canPlace(activePiece_)) {
        status_ = GameStatus::GameOver;
    }
}

bool Game::stepDown() {
    if (status_ != GameStatus::Running) {
        return false;
    }

    // Board coordinates increase downward, so the y offset is +1.
    if (tryMove(0, 1)) {
        return true;
    }

    lockActivePiece();
    return false;
}

void Game::lockActivePiece() {
    if (status_ != GameStatus::Running) {
        return;
    }

    // stepDown calls this only after a downward move has been rejected.
    board_.lockPiece(activePiece_);
    const int clearedRows = board_.clearFullRows();
    score_ += clearedRows * 100;
    spawnPiece();
}

void Game::handleAction(Action action) {
    if (status_ != GameStatus::Running) {
        return;
    }

    switch(action) {
        case Action::MoveLeft:
            tryMove(-1, 0);
            break;
        case Action::MoveRight:
            tryMove(1, 0);
            break;
        case Action::Rotate:
            tryRotate();
            break;
        case Action::SoftDrop:
            stepDown();
            break;
        case Action::HardDrop:
            // Move this piece as far as possible, then lock exactly once.
            while (tryMove(0, 1)) {}
            lockActivePiece();
            break;
        case Action::Quit:
            // Application handles quitting; it owns the program loop.
            break;
    }
}

void Game::update(double deltaTime) {
    if (status_ != GameStatus::Running
        || !std::isfinite(deltaTime) || deltaTime <= 0.0) {
        return;
    }

    fallTimer_ += deltaTime;

    // Catch up if more than one interval elapsed; retain fractional time.
    while (fallTimer_ >= fallInterval_) {
        fallTimer_ -= fallInterval_;

        if (!stepDown()) {
            // A new piece was spawned (and its timer reset), or play ended.
            // Do not spend the previous piece's leftover time on this one.
            break;
        }
    }
}
