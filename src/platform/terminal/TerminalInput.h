#pragma once
#include "../IInput.h"

class TerminalInput : public IInput {
public:
    std::vector<Action> pollActions() override;
};
