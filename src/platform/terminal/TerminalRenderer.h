#pragma once
#include "../IRenderer.h"

class TerminalRenderer : public IRenderer {
public:
    TerminalRenderer();
    ~TerminalRenderer() override;
    void render(const Game& game) override;

    // Exclusive responsibility for restoring terminal state.
    TerminalRenderer(const TerminalRenderer&) = delete;
    TerminalRenderer& operator=(const TerminalRenderer&) = delete;

private:
    void* outputHandle_ = nullptr;
    unsigned long originalMode_ = 0;
};
