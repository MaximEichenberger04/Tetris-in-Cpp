#pragma once
#include "../../core/GameSettings.h"

class RaylibMenu {
public:
    explicit RaylibMenu(bool classicAvailable = false) : classicAvailable_(classicAvailable) {}
    // Keep showing the menu. True means Start; false means close/Escape.
    bool run();
    // Let the caller read the choices after run() returns.
    const GameSettings& settings() const;

private:
    bool classicAvailable_;
    GameSettings settings_; // Remembers choices; defaults come from GameSettings.h.

    void draw() const; // Displays choices without changing them.
};
