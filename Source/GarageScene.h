#pragma once

#include "axmol.h"

class DoorButton;

class GarageScene : public ax::Scene
{
public:
    bool init() override;
    void update(float delta) override;

private:
    DoorButton* createDoor(std::string_view normalImage = "",
                           std::string_view hoverImage  = "",
                           const ax::Vec2& pos          = ax::Vec2());
};