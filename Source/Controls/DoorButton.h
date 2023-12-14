#pragma once

#include "axmol.h"
#include "ui/UIButton.h"

class DoorButton : public ax::ui::Button
{
public:
    DoorButton();

    static DoorButton* create(std::string_view normalImage = "",
                       std::string_view hoverImage  = "",
                       TextureResType texType       = TextureResType::LOCAL);

    bool init(std::string_view normalImage = "",
              std::string_view hoverImage  = "",
              TextureResType texType       = TextureResType::LOCAL);

protected:
    std::string _hoverFileName;
};