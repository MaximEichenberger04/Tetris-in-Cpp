#pragma once
class Game;

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void render(const Game& game) = 0;
};
