#pragma once

#include "axmol.h"

#include "Part.h"
#include "PartArea.h"

namespace car
{

class Frame : public ax::Sprite
{
    using PartAreas = std::vector<PartAreaPtr>;

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