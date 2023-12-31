#pragma once

#include "axmol.h"
#include "PartType.h"

namespace car
{

class Part;

class PartArea : public ax::Rect
{
public:
    PartArea();
    PartArea(float x, float y, float width, float height, PartType partType,
        float zOrder = 0.f);
    PartArea(const ax::Vec2& pos, const ax::Vec2& dimension, PartType partType,
        float zOrder = 0.f);
    PartArea(const PartArea& other);
    PartArea& operator=(const PartArea& other);

    void setPartType(PartType partType) noexcept;
    PartType getPartType() const noexcept;
    float getZOrder() const noexcept;

    bool partTypeEquals(PartType partType) const noexcept;
    void setInstalledPart(Part* part);
    Part* getInstalledPart() const noexcept;

private:
    PartType _partType;
    float _zOrder;
    Part* _installedPart;
};

using PartAreaPtr = std::shared_ptr<PartArea>;
using PartAreaWPtr = std::weak_ptr<PartArea>;

} // namespace car