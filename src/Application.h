#pragma once
#include <memory>
#include "core/Game.h"
#include "platform/IInput.h"
#include "platform/IRenderer.h"
#include "platform/terminal/MusicPlayer.h"

class Application {
public:
    Application(std::unique_ptr<IInput> input,
                std::unique_ptr<IRenderer> renderer,
                std::unique_ptr<MusicPlayer> music = nullptr,
                const GameSettings& settings = GameSettings{});
    void run();

private:
    Game game_;
    std::unique_ptr<IInput> input_;
    std::unique_ptr<IRenderer> renderer_;
    std::unique_ptr<MusicPlayer> music_;
};
