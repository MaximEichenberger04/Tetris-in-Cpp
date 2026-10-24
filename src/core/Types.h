#pragma once

// I: straight line, O: 2x2 Square, T: T-Shape, L: L-shape pointing right
// J: Mirrored L-shape (left), S: Right-handed skew, Z: Left-handed skew
enum class TetrominoType {
    I, O, T, L, J, S, Z
};

enum class Cell {
    Empty,
    I, O, T, L, J, S, Z
};

struct Position {
    int x = 0;
    int y = 0;
};

enum class Action {
    MoveLeft,
    MoveRight,
    Rotate,
    SoftDrop,
    HardDrop,
    Quit
};

enum class GameStatus {
    Running,
    GameOver
};