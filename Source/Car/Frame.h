#pragma once

#include "axmol.h"

namespace car
{

class Frame : public ax::Sprite
{
public:
    Frame();

    static Frame* create(std::string_view filename,
                         ax::PixelFormat format = ax::Texture2D::getDefaultAlphaPixelFormat());
};

} // namespace car