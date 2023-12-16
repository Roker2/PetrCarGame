#include "Part.h"

USING_NS_AX;

namespace car
{

Part::Part()
    : ui::Widget()
    , _previewSprite(nullptr)
    , _previewSpriteLoaded(false)
    , _previewFileName("")
    , _previewTexType(TextureResType::LOCAL)
{
}

Part* Part::create(std::string_view previewImage, ax::ui::Widget::TextureResType texType)
{
    Part* part = new Part();
    if (part->init(previewImage, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

bool Part::init(std::string_view previewImage, ax::ui::Widget::TextureResType texType)
{
    if (!Widget::init())
    {
        return false;
    }

    initPreviewTexture(previewImage, texType);

    return true;
}

PartType Part::getType() const noexcept
{
    return PartType::None;
}

void Part::initRenderer()
{
    _previewSprite = Sprite::create();
    addChild(_previewSprite);
}

void Part::initPreviewTexture(std::string_view filename, ui::Widget::TextureResType texType)
{
    _previewFileName = filename;
    _previewTexType = texType;
    if (_previewSpriteLoaded = !filename.empty();
        _previewSpriteLoaded)
    {
        switch (texType)
        {
        case TextureResType::LOCAL:
            _previewSprite->initWithFile(filename);
            break;
        case TextureResType::PLIST:
            _previewSprite->initWithSpriteFrameName(filename);
            break;
        default:
            break;
        }
    }
}

} // namespace car