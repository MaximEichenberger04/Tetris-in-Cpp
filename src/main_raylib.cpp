#include "Application.h"
#include "platform/raylib/RaylibWindow.h"
#include "platform/raylib/RaylibInput.h"
#include "platform/raylib/RaylibRenderer.h"
#include "platform/raylib/RaylibMenu.h"
#include <exception>
#include <iostream>
#include <memory>

int main() {
    try {
        // Declared first: stays alive until after app and its renderer are gone.
        RaylibWindow window;
        RaylibMenu menu(MusicPlayer::isAvailable(MusicTrack::Classic));
        if (!menu.run()) return 0;
        const GameSettings settings = menu.settings();
        std::unique_ptr<MusicPlayer> music;
        if (settings.musicEnabled) music = std::make_unique<MusicPlayer>(settings.musicTrack);
        Application app(std::make_unique<RaylibInput>(),
                        std::make_unique<RaylibRenderer>(),
                        std::move(music), settings);
        app.run();
    } catch (const std::exception& error) {
        std::cerr << "Tetris: " << error.what() << '\n';
        return 1;
    }
}
