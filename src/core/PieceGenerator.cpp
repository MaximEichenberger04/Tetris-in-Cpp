#include "PieceGenerator.h"

#include <algorithm>

PieceGenerator::PieceGenerator() {
    // Seed the engine once when this object is created.
    std::random_device seedSource;
    generator_.seed(seedSource());
    refillBag();
}

TetrominoType PieceGenerator::next() {
    if (nextIndex_ == bag_.size()) {
        refillBag();
    }

    const TetrominoType type = bag_[nextIndex_];
    ++nextIndex_;
    return type;
}

void PieceGenerator::refillBag() {
    // Drawing pieces only advances the index; all seven values remain here.
    std::shuffle(bag_.begin(), bag_.end(), generator_);
    nextIndex_ = 0;
}
