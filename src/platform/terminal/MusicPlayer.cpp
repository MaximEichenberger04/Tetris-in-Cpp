#include "MusicPlayer.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <mmsystem.h>
#include <stdexcept>

MusicPlayer::~MusicPlayer() {
    stop();
}

bool MusicPlayer::isAvailable(MusicTrack track) {
    const int id = track == MusicTrack::Custom ? 101 : 102;
    return FindResourceW(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(id), L"WAVE") != nullptr;
}

void MusicPlayer::playLoop() {
    if (playing_) return; // Do not restart the track every frame.

    // Custom is resource 101; optional classic recording is resource 102.
    const int id = track_ == MusicTrack::Custom ? 101 : 102;
    if (!PlaySoundW(MAKEINTRESOURCEW(id), GetModuleHandleW(nullptr),
                    SND_RESOURCE | SND_ASYNC | SND_LOOP | SND_NODEFAULT)) {
        throw std::runtime_error("Could not play the embedded soundtrack.");
    }
    playing_ = true;
}

void MusicPlayer::stop() {
    if (!playing_) return;
    PlaySoundW(nullptr, nullptr, 0);
    playing_ = false;
}
