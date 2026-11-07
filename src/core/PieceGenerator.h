#pragma once

#include "Types.h"
#include <array>
#include <cstddef>
#include <random>

class PieceGenerator {
public:
    PieceGenerator(); // constructor
    TetrominoType next(); // return next TetrominoType

private:
    // Each bag contains exactly one of each piece type. -> fixed size
    std::array<TetrominoType, 7> bag_ = {
        TetrominoType::I, TetrominoType::O, TetrominoType::T,
        TetrominoType::S, TetrominoType::Z, TetrominoType::J,
        TetrominoType::L
    };

    // Index of the next entry to return: 0 through 6; 7 means exhausted.
    std::size_t nextIndex_ = 0;

    // Keep one engine alive so its random sequence advances between shuffles.
    std::mt19937 generator_;

    void refillBag();
};
