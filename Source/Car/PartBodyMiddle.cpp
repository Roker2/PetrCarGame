#include "PartBodyMiddle.h"

namespace car
{

PartBodyMiddle::PartBodyMiddle()
    : PartTwoLayer()
    , PartBodyBase()
{
}

PartBodyMiddle* PartBodyMiddle::create(std::string_view previewImage,
    std::string_view normalFrontImage,
    std::string_view normalBackImage,
    const ax::Vec2& frontImagePos,
    const ax::Vec2& backImagePos,
    TextureResType texType)
{
    PartBodyMiddle* part = new PartBodyMiddle();
    if (part->init(previewImage, normalFrontImage, normalBackImage,
        frontImagePos, backImagePos, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartType PartBodyMiddle::getType() const noexcept
{
    return PartType::BodyMiddle;
}

} // namespace car