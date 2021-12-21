#pragma once

#include "Engine.h"

class OrbitalGame : public Game {
public:
    OrbitalGame() : Game() {}
protected:
    void LoadData() override;
};
