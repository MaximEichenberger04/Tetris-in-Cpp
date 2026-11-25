#include "Application.h"
#include <algorithm>
#include <chrono>
#include <stdexcept>
#include <thread>
#include <utility>

Application::Application(std::unique_ptr<IInput> input,
                         std::unique_ptr<IRenderer> renderer,
                         std::unique_ptr<MusicPlayer> music,
                         const GameSettings& settings)
    : game_(settings), input_(std::move(input)), renderer_(std::move(renderer)),
      music_(std::move(music))
{
    if (!input_ || !renderer_) {
        throw std::invalid_argument("Application requires input and renderer objects.");
    }
    if (!settings.musicEnabled) music_.reset();
}

void Application::run() {
    using Clock = std::chrono::steady_clock;
    auto previous = Clock::now();

    while (true) {
        const auto now = Clock::now();
        const double elapsed = std::chrono::duration<double>(now - previous).count();
        previous = now;
        const auto actions = input_->pollActions();
        if (std::find(actions.begin(), actions.end(), Action::Quit) != actions.end()) {
            if (music_) music_->stop();
            return;
        }

        // Apply past time before current actions so a hard drop cannot charge
        // the previous frame's time to the newly spawned piece.
        // Cap long window/terminal stalls for comfortable play.
        game_.update(std::min(elapsed, 0.25));
        for (Action action : actions) {
            game_.handleAction(action);
        }
        if (music_) {
            if (game_.status() == GameStatus::Running) {
                music_->playLoop();
            } else {
                music_->stop();
            }
        }
        renderer_->render(game_);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}
