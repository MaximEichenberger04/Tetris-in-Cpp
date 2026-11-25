#include "RaylibWindow.h"
#include "raylib.h"
#include <stdexcept>

RaylibWindow::RaylibWindow() {
    // Board: 20px top margin + 20 rows * 32px = 660px; leave 40px below.
    InitWindow(1200, 700, "Tetris");
    if (!IsWindowReady()) {
        throw std::runtime_error("Could not create the raylib window.");
    }
    // Application already sleeps between frames; avoid a second FPS limiter.
}

RaylibWindow::~RaylibWindow() {
    CloseWindow();
}
