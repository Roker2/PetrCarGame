#include "PartGearbox.h"

namespace car
{

PartGearbox::PartGearbox()
    : PartOneLayer()
    , acceleration(0)
{
}

PartGearbox* PartGearbox::create(std::string_view previewImage,
    std::string_view normalImage,
    const ax::Vec2& installedOffset,
    std::string_view installSoundPath,
    ax::ui::Widget::TextureResType texType)
{
    PartGearbox* part = new PartGearbox();
    if (part->init(previewImage, normalImage, installedOffset, installSoundPath, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartGearbox* PartGearbox::createFromJson(std::string_view filename)
{
    PartGearbox* part = new PartGearbox();
    if (part->loadFromJson(filename))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartType PartGearbox::getType() const noexcept
{
    return PartType::Gearbox;
}

} // namespace car