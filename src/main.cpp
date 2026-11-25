#include "Application.h"
#include "platform/terminal/TerminalInput.h"
#include "platform/terminal/TerminalRenderer.h"

#include <exception>
#include <iostream>
#include <memory>

int main() {
    try {
        Application app(std::make_unique<TerminalInput>(),
                        std::make_unique<TerminalRenderer>(),
                        std::make_unique<MusicPlayer>());
        app.run();
    } catch (const std::exception& error) {
        std::cerr << "Tetris: " << error.what() << '\n';
        return 1;
    }
}
