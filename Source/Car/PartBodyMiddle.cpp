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
    const ax::Vec2& installedOffset,
    std::string_view installSoundPath,
    TextureResType texType)
{
    PartBodyMiddle* part = new PartBodyMiddle();
    if (part->init(previewImage, normalFrontImage, normalBackImage,
        frontImagePos, backImagePos, installedOffset, installSoundPath, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartBodyMiddle* PartBodyMiddle::createFromJson(std::string_view filename)
{
    PartBodyMiddle* part = new PartBodyMiddle();
    if (part->loadFromJson(filename))
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