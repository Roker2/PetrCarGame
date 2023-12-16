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
    setTouchEnabled(true);
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
    setContentSize(_previewSprite->getContentSize());

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

bool Part::onTouchBegan(ax::Touch* touch, ax::Event* event)
{
    if (!Widget::onTouchBegan(touch, event))
    {
        return false;
    }
    if (getBoundingBox().containsPoint(touch->getLocation()))
    {
#if _AX_DEBUG > 0
        AXLOG("Part contain touch");
#endif
        return true;
    }
    return false;
}

void Part::onTouchMoved(ax::Touch* touch, ax::Event* event)
{
    Widget::onTouchMoved(touch, event);
    auto newPos = getPosition() + touch->getDelta();
    if (const auto parent = getParent();
        parent)
    {
        const auto& parentSize = parent->getContentSize();

        const auto minX = _contentSize.x / 2.f;
        const auto minY = _contentSize.y / 2.f;
        const auto maxX = parentSize.x - minX;
        const auto maxY = parentSize.y - minY;

        newPos.x = std::min(std::max(newPos.x, minX), maxX);
        newPos.y = std::min(std::max(newPos.y, minY), maxY);
    }
#if _AX_DEBUG > 0
    else
    {
        AXLOGWARN("No part parent");
    }
#endif
    setPosition(newPos);
}

void Part::onTouchEnded(ax::Touch* touch, ax::Event* event)
{
    Widget::onTouchEnded(touch, event);
}

} // namespace car