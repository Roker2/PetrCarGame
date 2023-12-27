#include "Part.h"

USING_NS_AX;

namespace car
{

Part::Part()
    : ui::Widget()
    , weight(0)
    , _previewSprite(nullptr)
    , _previewSpriteLoaded(false)
    , _previewFileName("")
    , _previewTexType(TextureResType::LOCAL)
    , _onTouchMovingCallback(nullptr)
    , _isInstalled(false)
    , _installedOffset()
{
    setTouchEnabled(true);
}

Part* Part::create(std::string_view previewImage,
    const ax::Vec2& installedOffset,
    ax::ui::Widget::TextureResType texType)
{
    Part* part = new Part();
    if (part->init(previewImage, installedOffset, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

bool Part::init(std::string_view previewImage,
    const ax::Vec2& installedOffset,
    ax::ui::Widget::TextureResType texType)
{
    if (!Widget::init())
    {
        return false;
    }

    initPreviewTexture(previewImage, texType);
    setContentSize(_previewSprite->getContentSize());
    _previewSprite->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);

    _installedOffset = installedOffset;

    return true;
}

void Part::SetOnTouchMovingCallback(onTouchMovingCallback callback) noexcept
{
    _onTouchMovingCallback = callback;
}

PartType Part::getType() const noexcept
{
    return PartType::None;
}

void Part::setInstalled()
{

}

void Part::setPreview()
{

}

bool Part::getIsInstalled() const noexcept
{
    return _isInstalled;
}

const Vec2& Part::getInstalledOffset() const noexcept
{
    return _installedOffset;
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

    if (_onTouchMovingCallback)
    {
        _onTouchMovingCallback(touch, event);
    }
}

void Part::onTouchEnded(ax::Touch* touch, ax::Event* event)
{
    Widget::onTouchEnded(touch, event);
}

} // namespace car