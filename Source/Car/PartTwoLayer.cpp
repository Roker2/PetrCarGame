#include "PartTwoLayer.h"
#include "JSONDefault/JSONBasic.h"

USING_NS_AX;
USING_NS_AX_EXT;

namespace
{
const char* normalFrontFileNameProp = "normalFrontFileName";
const char* normalFrontTexTypeProp = "normalFrontTexType";
const char* normalBackFileNameProp = "normalBackFileName";
const char* normalBackTexTypeProp = "normalBackTexType";
const char* frontImagePosXProp = "frontImagePosX";
const char* frontImagePosYProp = "frontImagePosY";
const char* backImagePosXProp = "backImagePosX";
const char* backImagePosYProp = "backImagePosY";
} // namespace

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
                                   const ax::Vec2& installedOffset,
                                   TextureResType texType)
{
    PartTwoLayer* part = new PartTwoLayer();
    if (part->init(previewImage, normalFrontImage, normalBackImage,
        frontImagePos, backImagePos, installedOffset, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartTwoLayer* PartTwoLayer::createFromJson(std::string_view filename)
{
    PartTwoLayer* part = new PartTwoLayer();
    if (part->loadFromJson(filename))
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
                        const ax::Vec2& installedOffset,
                        TextureResType texType)
{
    if (!Part::init(previewImage, installedOffset, texType))
    {
        return false;
    }

    initNormalFrontTexture(normalFrontImage, texType);
    initNormalBackTexture(normalBackImage, texType);

    commonInit(frontImagePos, backImagePos);

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

void PartTwoLayer::setGlobalZOrder(float globalZOrder)
{
    Part::setGlobalZOrder(globalZOrder);
    if (_isInstalled)
    {
        _normalFrontSprite->setGlobalZOrder(globalZOrder);
        _normalBackSprite->setGlobalZOrder(globalZOrder - 4.f);
    }
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

void PartTwoLayer::savePropertiesToJson(JSONBasic* jsonBasic) const
{
    Part::savePropertiesToJson(jsonBasic);
    jsonBasic->setStringForKey(normalFrontFileNameProp, _normalFrontFileName.c_str());
    jsonBasic->setIntegerForKey(normalFrontTexTypeProp, static_cast<int>(_normalFrontTexType));
    jsonBasic->setStringForKey(normalBackFileNameProp, _normalBackFileName.c_str());
    jsonBasic->setIntegerForKey(normalBackTexTypeProp, static_cast<int>(_normalBackTexType));

    jsonBasic->setFloatForKey(frontImagePosXProp, _normalFrontSprite->getPositionX());
    jsonBasic->setFloatForKey(frontImagePosYProp, _normalFrontSprite->getPositionY());
    jsonBasic->setFloatForKey(backImagePosXProp, _normalBackSprite->getPositionX());
    jsonBasic->setFloatForKey(backImagePosYProp, _normalBackSprite->getPositionY());
}

void PartTwoLayer::loadPropertiesFromJson(JSONBasic* jsonBasic)
{
    Part::loadPropertiesFromJson(jsonBasic);
    auto normalFrontFileName = jsonBasic->getStringForKey(normalFrontFileNameProp);
    auto normalFrontTexType = static_cast<TextureResType>(jsonBasic->getIntegerForKey(normalFrontTexTypeProp));
    initNormalFrontTexture(normalFrontFileName, normalFrontTexType);
    auto normalBackFileName = jsonBasic->getStringForKey(normalBackFileNameProp);
    auto normalBackTexType = static_cast<TextureResType>(jsonBasic->getIntegerForKey(normalBackTexTypeProp));
    initNormalBackTexture(normalBackFileName, normalBackTexType);

    Vec2 frontImagePos;
    frontImagePos.x = jsonBasic->getFloatForKey(frontImagePosXProp);
    frontImagePos.y = jsonBasic->getFloatForKey(frontImagePosYProp);
    Vec2 backImagePos;
    backImagePos.x = jsonBasic->getFloatForKey(backImagePosXProp);
    backImagePos.y = jsonBasic->getFloatForKey(backImagePosYProp);

    commonInit(frontImagePos, backImagePos);
}

void PartTwoLayer::commonInit(const Vec2& frontImagePos,
    const Vec2& backImagePos)
{
    if (_normalFrontSpriteLoaded
        && _normalBackSpriteLoaded)
    {
        _normalFrontSprite->setVisible(false);
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
    }
    else
    {
        AXLOGERROR("Normal sprites are not loaded!");
    }
}

} // namespace car