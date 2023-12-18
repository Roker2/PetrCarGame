#include "PartSeat.h"

namespace car
{

PartType PartSeat::getType() const noexcept
{
    return PartType::Seat;
}

PartSeat* PartSeat::create(std::string_view previewImage,
                           std::string_view normalImage,
                           TextureResType texType)
{
    PartSeat* part = new PartSeat();
    if (part->init(previewImage, normalImage, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

} // namespace car