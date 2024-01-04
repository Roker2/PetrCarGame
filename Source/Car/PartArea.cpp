#include "PartArea.h"

#include "Part.h"

USING_NS_AX;

namespace car
{

PartArea::PartArea()
    : Rect()
    , _partType(PartType::None)
    , _installedPart(nullptr)
{
}

PartArea::PartArea(float x, float y, float width, float height, PartType partType,
    float zOrder)
    : Rect(x, y, width, height)
    , _partType(partType)
    , _zOrder(zOrder)
{
}

PartArea::PartArea(const Vec2& pos, const Vec2& dimension, PartType partType,
    float zOrder)
    : Rect(pos, dimension)
    , _partType(partType)
    , _zOrder(zOrder)
{
}

PartArea::PartArea(const PartArea& other)
    : Rect(other)
    , _partType(other._partType)
    , _zOrder(other._zOrder)
    , _installedPart(nullptr)
{
}

PartArea& PartArea::operator=(const PartArea& other)
{
    Rect::operator=(other);
    _partType = other._partType;
    _zOrder = other._zOrder;
    return *this;
}

void PartArea::setPartType(PartType partType) noexcept
{
    _partType = partType;
}

PartType PartArea::getPartType() const noexcept
{
    return _partType;
}

float PartArea::getZOrder() const noexcept
{
    return _zOrder;
}

bool PartArea::partTypeEquals(PartType partType) const noexcept
{
    return _partType == partType;
}

void PartArea::setInstalledPart(Part* part)
{
    _installedPart = part;
}

} // namespace car