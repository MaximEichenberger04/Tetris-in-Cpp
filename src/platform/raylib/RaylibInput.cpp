#include "RaylibInput.h"
#include "raylib.h"

namespace {
    bool pressedOrRepeated(int key) {
        return IsKeyPressed(key) || IsKeyPressedRepeat(key);
    }
}

std::vector<Action> RaylibInput::pollActions() {
    if (WindowShouldClose() || IsKeyPressed(KEY_Q)) {
        return {Action::Quit};
    }

    std::vector<Action> actions;
    if (pressedOrRepeated(KEY_A) || pressedOrRepeated(KEY_LEFT))
        actions.push_back(Action::MoveLeft);
    if (pressedOrRepeated(KEY_D) || pressedOrRepeated(KEY_RIGHT))
        actions.push_back(Action::MoveRight);
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
        actions.push_back(Action::Rotate);
    if (pressedOrRepeated(KEY_S) || pressedOrRepeated(KEY_DOWN))
        actions.push_back(Action::SoftDrop);
    if (IsKeyPressed(KEY_SPACE))
        actions.push_back(Action::HardDrop);
    return actions;
}
