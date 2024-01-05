#include "PartEngine.h"

namespace car
{

PartEngine::PartEngine()
    : PartOneLayer()
    , speed(0)
    , fuelConsumption(0)
    , strength(0)
{
}

PartEngine* PartEngine::create(std::string_view previewImage,
                               std::string_view normalImage,
                               const ax::Vec2& installedOffset,
                               std::string_view installSoundPath,
                               TextureResType texType)
{
    PartEngine* part = new PartEngine();
    if (part->init(previewImage, normalImage, installedOffset, installSoundPath, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartEngine* PartEngine::createFromJson(std::string_view filename)
{
    PartEngine* part = new PartEngine();
    if (part->loadFromJson(filename))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartType PartEngine::getType() const noexcept
{
    return PartType::Engine;
}

} // namespace car