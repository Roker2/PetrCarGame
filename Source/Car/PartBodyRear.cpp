#include "PartBodyRear.h"

namespace car
{

PartBodyRear::PartBodyRear()
    : PartTwoLayer()
    , PartBodyBase()
{
}

PartBodyRear* PartBodyRear::create(std::string_view previewImage,
    std::string_view normalFrontImage,
    std::string_view normalBackImage,
    const ax::Vec2& frontImagePos,
    const ax::Vec2& backImagePos,
    const ax::Vec2& installedOffset,
    std::string_view installSoundPath,
    TextureResType texType)
{
    PartBodyRear* part = new PartBodyRear();
    if (part->init(previewImage, normalFrontImage, normalBackImage,
        frontImagePos, backImagePos, installedOffset, installSoundPath, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartBodyRear* PartBodyRear::createFromJson(std::string_view filename)
{
    PartBodyRear* part = new PartBodyRear();
    if (part->loadFromJson(filename))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartType PartBodyRear::getType() const noexcept
{
    return PartType::BodyRear;
}

} // namespace car