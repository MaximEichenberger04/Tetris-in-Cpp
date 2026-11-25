#pragma once
#include <vector>
#include "../core/Types.h"

class IInput {
public:
    virtual ~IInput() = default;
    virtual std::vector<Action> pollActions() = 0;
};
