#include "PartSeat.h"

namespace car
{

PartSeat::PartSeat()
    : PartOneLayer()
    , comfort(0)
{
}

PartSeat* PartSeat::create(std::string_view previewImage,
                           std::string_view normalImage,
                           const ax::Vec2& installedOffset,
                           std::string_view installSoundPath,
                           TextureResType texType)
{
    PartSeat* part = new PartSeat();
    if (part->init(previewImage, normalImage, installedOffset, installSoundPath, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartSeat* PartSeat::createFromJson(std::string_view filename)
{
    PartSeat* part = new PartSeat();
    if (part->loadFromJson(filename))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartType PartSeat::getType() const noexcept
{
    return PartType::Seat;
}

} // namespace car