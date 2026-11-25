#pragma once

enum class Difficulty { // speed of tetrominos dropping
    Easy,
    Medium,
    Hard
};

enum class RandomizerMode { // random pieces or bag of 7 
    Independent,
    SevenBag
};

enum class MusicTrack { // tetris track or own track
    Classic,
    Custom
};

struct GameSettings {
    Difficulty difficulty = Difficulty::Medium;
    RandomizerMode randomizer = RandomizerMode::SevenBag;
    bool musicEnabled = true;
    MusicTrack musicTrack = MusicTrack::Custom;
};