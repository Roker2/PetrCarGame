#pragma once

#include "axmol.h"

class GarageScene : public ax::Scene
{
public:
    bool init() override;
    void update(float delta) override;
};