#include "TerminalInput.h"
#include <conio.h>

std::vector<Action> TerminalInput::pollActions() {
    std::vector<Action> actions;
    // Checks availability without waiting for Enter.
    while (_kbhit()) {
        const int key = _getch();
        // Windows special keys have a prefix followed by a key code.
        if (key == 0 || key == 224) {
            switch (_getch()) {
                case 75: actions.push_back(Action::MoveLeft); break;
                case 77: actions.push_back(Action::MoveRight); break;
                case 72: actions.push_back(Action::Rotate); break;
                case 80: actions.push_back(Action::SoftDrop); break;
            }
            continue;
        }
        switch (key) {
            case 'a': case 'A': actions.push_back(Action::MoveLeft); break;
            case 'd': case 'D': actions.push_back(Action::MoveRight); break;
            case 'w': case 'W': actions.push_back(Action::Rotate); break;
            case 's': case 'S': actions.push_back(Action::SoftDrop); break;
            case ' ': actions.push_back(Action::HardDrop); break;
            case 'q': case 'Q': case 27:
                actions.push_back(Action::Quit);
                return actions;
        }
    }
    return actions;
}
