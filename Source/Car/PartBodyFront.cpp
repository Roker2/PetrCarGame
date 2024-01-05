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
                           const ax::Vec2& installedOffset,
                           std::string_view installSoundPath,
                           TextureResType texType)
{
    PartBodyFront* part = new PartBodyFront();
    if (part->init(previewImage, normalImage, installedOffset, installSoundPath, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartBodyFront* PartBodyFront::createFromJson(std::string_view filename)
{
    PartBodyFront* part = new PartBodyFront();
    if (part->loadFromJson(filename))
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