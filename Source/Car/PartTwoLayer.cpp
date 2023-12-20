#include "PartTwoLayer.h"

USING_NS_AX;

namespace car
{

PartTwoLayer::PartTwoLayer()
    : Part()
    , _normalFrontSprite(nullptr)
    , _normalBackSprite(nullptr)
    , _normalFrontSpriteLoaded(false)
    , _normalBackSpriteLoaded(false)
    , _normalFrontFileName("")
    , _normalBackFileName("")
    , _normalFrontTexType(TextureResType::LOCAL)
    , _normalBackTexType(TextureResType::LOCAL)
{
}

PartTwoLayer* PartTwoLayer::create(std::string_view previewImage,
                                   std::string_view normalFrontImage,
                                   std::string_view normalBackImage,
                                   const ax::Vec2& frontImagePos,
                                   const ax::Vec2& backImagePos,
                                   TextureResType texType)
{
    PartTwoLayer* part = new PartTwoLayer();
    if (part->init(previewImage, normalFrontImage, normalBackImage,
        frontImagePos, backImagePos, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

bool PartTwoLayer::init(std::string_view previewImage,
                        std::string_view normalFrontImage,
                        std::string_view normalBackImage,
                        const ax::Vec2& frontImagePos,
                        const ax::Vec2& backImagePos,
                        TextureResType texType)
{
    if (!Part::init(previewImage, texType))
    {
        return false;
    }

    initNormalFrontTexture(normalFrontImage, texType);
    _normalFrontSprite->setVisible(false);

    initNormalBackTexture(normalBackImage, texType);
    _normalBackSprite->setVisible(false);

    const auto& frontContentSize = _normalFrontSprite->getContentSize();
    const auto& backContentSize = _normalBackSprite->getContentSize();
    const auto diffSize = _normalFrontSprite->getContentSize() - _normalBackSprite->getContentSize();

    _normalContentSize.x = std::fmaxf(backContentSize.x / 2.f + backImagePos.x,
        frontContentSize.x / 2.f + frontImagePos.x);
    _normalContentSize.y = std::fmaxf(backContentSize.y / 2.f + backImagePos.y,
        frontContentSize.y / 2.f + frontImagePos.y);

    _normalFrontSprite->setPosition(frontImagePos);
    _normalBackSprite->setPosition(backImagePos);

    return true;
}

void PartTwoLayer::setInstalled()
{
    if (_isInstalled)
    {
        return;
    }
    _isInstalled = true;
    _normalFrontSprite->setVisible(true);
    _normalBackSprite->setVisible(true);
    setContentSize(_normalContentSize);
    _previewSprite->setVisible(false);
}

void PartTwoLayer::setPreview()
{
    if (!_isInstalled)
    {
        return;
    }
    _isInstalled = false;
    _previewSprite->setVisible(true);
    setContentSize(_previewSprite->getContentSize());
    _normalFrontSprite->setVisible(false);
    _normalBackSprite->setVisible(false);
}

void PartTwoLayer::initRenderer()
{
    Part::initRenderer();
    _normalBackSprite = Sprite::create();
    addChild(_normalBackSprite);
    _normalFrontSprite = Sprite::create();
    addChild(_normalFrontSprite);
}

void PartTwoLayer::initNormalFrontTexture(std::string_view filename,
                                          ui::Widget::TextureResType texType)
{
    _normalFrontFileName = filename;
    _normalFrontTexType = texType;
    if (_normalFrontSpriteLoaded = !filename.empty();
        _normalFrontSpriteLoaded)
    {
        switch (texType)
        {
        case TextureResType::LOCAL:
            _normalFrontSprite->initWithFile(filename);
            break;
        case TextureResType::PLIST:
            _normalFrontSprite->initWithSpriteFrameName(filename);
            break;
        default:
            break;
        }
    }
}

void PartTwoLayer::initNormalBackTexture(std::string_view filename,
                                               ui::Widget::TextureResType texType)
{
    _normalBackFileName = filename;
    _normalBackTexType = texType;
    if (_normalBackSpriteLoaded = !filename.empty();
        _normalBackSpriteLoaded)
    {
        switch (texType)
        {
        case TextureResType::LOCAL:
            _normalBackSprite->initWithFile(filename);
            break;
        case TextureResType::PLIST:
            _normalBackSprite->initWithSpriteFrameName(filename);
            break;
        default:
            break;
        }
    }
}

} // namespace car