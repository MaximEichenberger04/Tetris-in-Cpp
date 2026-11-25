#pragma once
#include "../IRenderer.h"

class RaylibRenderer : public IRenderer {
public:
    void render(const Game& game) override;
};
