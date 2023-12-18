#include "PartArea.h"

USING_NS_AX;

namespace car
{

PartArea::PartArea()
    : Rect()
    , _partType(PartType::None)
{
}

PartArea::PartArea(float x, float y, float width, float height, PartType partType)
    : Rect(x, y, width, height)
    , _partType(partType)
{
}

PartArea::PartArea(const Vec2& pos, const Vec2& dimension, PartType partType)
    : Rect(pos, dimension)
    , _partType(partType)
{
}

PartArea::PartArea(const PartArea& other)
    : Rect(other)
    , _partType(other._partType)
{
}

PartArea& PartArea::operator=(const PartArea& other)
{
    Rect::operator=(other);
    _partType = other._partType;
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

bool PartArea::partTypeEquals(PartType partType) const noexcept
{
    return _partType == partType;
}

} // namespace car