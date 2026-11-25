#pragma once

// Owns the window. Construct this before Application and destroy it afterward.
class RaylibWindow {
public:
    RaylibWindow();
    ~RaylibWindow();
    RaylibWindow(const RaylibWindow&) = delete;
    RaylibWindow& operator=(const RaylibWindow&) = delete;
};
