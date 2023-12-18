#pragma once

#include "axmol.h"
#include "PartType.h"

namespace car
{

class PartArea : public ax::Rect
{
public:
    PartArea();
    PartArea(float x, float y, float width, float height, PartType partType);
    PartArea(const ax::Vec2& pos, const ax::Vec2& dimension, PartType partType);
    PartArea(const PartArea& other);
    PartArea& operator=(const PartArea& other);

    void setPartType(PartType partType) noexcept;
    PartType getPartType() const noexcept;

    bool partTypeEquals(PartType partType) const noexcept;

private:
    PartType _partType;
};

} // namespace car