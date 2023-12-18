#pragma once

#include "axmol.h"

namespace car
{

class Part;
class PartArea;

class Frame : public ax::Sprite
{
    using PartAreas = std::vector<PartArea>;

public:
    Frame();

    static Frame* create(std::string_view filename,
                         ax::PixelFormat format = ax::Texture2D::getDefaultAlphaPixelFormat());

    virtual bool initWithFile(std::string_view filename, ax::PixelFormat format) override;

    void onPartTouchMoved(Part* part, ax::Touch* touch, ax::Event* event);

private:
    PartAreas _partAreas;
};

} // namespace car