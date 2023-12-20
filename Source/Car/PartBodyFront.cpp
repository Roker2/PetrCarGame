#include "PartBodyFront.h"

namespace car
{

PartBodyFront::PartBodyFront()
    : PartOneLayer()
    , PartBodyBase()
    , funnyFactor(0)
{
}

PartBodyFront* PartBodyFront::create(std::string_view previewImage,
                           std::string_view normalImage,
                           TextureResType texType)
{
    PartBodyFront* part = new PartBodyFront();
    if (part->init(previewImage, normalImage, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartType PartBodyFront::getType() const noexcept
{
    return PartType::BodyFront;
}

} // namespace car