#include "RaylibMenu.h"
#include "raylib.h"
#include <chrono>
#include <thread>

namespace {
    const Rectangle easyButton{300, 190, 180, 45};
    const Rectangle mediumButton{510, 190, 180, 45};
    const Rectangle hardButton{720, 190, 180, 45};
    const Rectangle independentButton{300, 290, 285, 45};
    const Rectangle bagButton{615, 290, 285, 45};
    const Rectangle musicOnButton{300, 390, 180, 45};
    const Rectangle musicOffButton{510, 390, 180, 45};
    const Rectangle classicButton{300, 490, 285, 45};
    const Rectangle customButton{615, 490, 285, 45};
    const Rectangle startButton{510, 600, 180, 45};

    void button(Rectangle bounds, const char* label, bool selected, bool enabled = true) {
        const Color fill = !enabled ? Color{40, 42, 50, 255}
                                   : (selected ? DARKGREEN : DARKGRAY);
        DrawRectangleRec(bounds, fill);
        DrawText(label, static_cast<int>(bounds.x) + 15,
                 static_cast<int>(bounds.y) + 12, 20, enabled ? RAYWHITE : GRAY);
    }
}

const GameSettings& RaylibMenu::settings() const {
    return settings_;
}

bool RaylibMenu::run() {
    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            const Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, easyButton))
                settings_.difficulty = Difficulty::Easy;
            else if (CheckCollisionPointRec(mouse, mediumButton))
                settings_.difficulty = Difficulty::Medium;
            else if (CheckCollisionPointRec(mouse, hardButton))
                settings_.difficulty = Difficulty::Hard;
            else if (CheckCollisionPointRec(mouse, independentButton))
                settings_.randomizer = RandomizerMode::Independent;
            else if (CheckCollisionPointRec(mouse, bagButton))
                settings_.randomizer = RandomizerMode::SevenBag;
            else if (CheckCollisionPointRec(mouse, musicOnButton))
                settings_.musicEnabled = true;
            else if (CheckCollisionPointRec(mouse, musicOffButton))
                settings_.musicEnabled = false;
            else if (CheckCollisionPointRec(mouse, classicButton)
                     && classicAvailable_ && settings_.musicEnabled)
                settings_.musicTrack = MusicTrack::Classic;
            else if (CheckCollisionPointRec(mouse, customButton) && settings_.musicEnabled)
                settings_.musicTrack = MusicTrack::Custom;
            else if (CheckCollisionPointRec(mouse, startButton))
                return true;
        }
        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    return false;
}

void RaylibMenu::draw() const {
    BeginDrawing();
    ClearBackground(Color{20, 22, 30, 255});
    DrawText("TETRIS", 500, 60, 48, RAYWHITE);
    DrawText("Difficulty - falling speed", 300, 155, 22, RAYWHITE);
    button(easyButton, "Easy: 0.8s", settings_.difficulty == Difficulty::Easy);
    button(mediumButton, "Medium: 0.5s", settings_.difficulty == Difficulty::Medium);
    button(hardButton, "Hard: 0.25s", settings_.difficulty == Difficulty::Hard);
    DrawText("Piece generation", 300, 255, 22, RAYWHITE);
    button(independentButton, "Independent random", settings_.randomizer == RandomizerMode::Independent);
    button(bagButton, "Seven-bag", settings_.randomizer == RandomizerMode::SevenBag);
    DrawText("Music", 300, 355, 22, RAYWHITE);
    button(musicOnButton, "On", settings_.musicEnabled);
    button(musicOffButton, "Off", !settings_.musicEnabled);
    DrawText("Soundtrack", 300, 455, 22, RAYWHITE);
    button(classicButton, "Classic", settings_.musicTrack == MusicTrack::Classic,
           classicAvailable_ && settings_.musicEnabled);
    button(customButton, "My version", settings_.musicTrack == MusicTrack::Custom,
           settings_.musicEnabled);
    if (!classicAvailable_)
        DrawText("Classic unavailable: add assets/classic.wav and rebuild.", 300, 550, 18, GRAY);
    button(startButton, "START", true);
    DrawText("Escape: close", 300, 665, 18, LIGHTGRAY);
    EndDrawing();
}
