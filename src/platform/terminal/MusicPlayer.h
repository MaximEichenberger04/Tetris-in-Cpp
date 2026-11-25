#pragma once
#include "../../core/GameSettings.h"

class MusicPlayer {
public:
    explicit MusicPlayer(MusicTrack track = MusicTrack::Custom) : track_(track) {}
    static bool isAvailable(MusicTrack track);
    ~MusicPlayer();
    MusicPlayer(const MusicPlayer&) = delete;
    MusicPlayer& operator=(const MusicPlayer&) = delete;

    void playLoop();
    void stop();

private:
    MusicTrack track_;
    bool playing_ = false;
};
