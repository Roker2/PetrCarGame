#include "PartOneLayer.h"
#include "JSONDefault/JSONBasic.h"

USING_NS_AX;
USING_NS_AX_EXT;

namespace
{
const char* normalFileNameProp = "normalFileName";
const char* normalTexTypeProp = "normalTexType";
} // namespace

namespace car
{

PartOneLayer::PartOneLayer()
    : Part()
    , _normalSprite(nullptr)
    , _normalSpriteLoaded(true)
    , _normalFileName("")
    , _normalTexType(TextureResType::LOCAL)
{
}

PartOneLayer* PartOneLayer::create(std::string_view previewImage,
                                   std::string_view normalImage,
                                   const Vec2& installedOffset,
                                   ui::Widget::TextureResType texType)
{
    PartOneLayer* part = new PartOneLayer();
    if (part->init(previewImage, normalImage, installedOffset, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

PartOneLayer* PartOneLayer::createFromJson(std::string_view filename)
{
    PartOneLayer* part = new PartOneLayer();
    if (part->loadFromJson(filename))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

bool PartOneLayer::init(std::string_view previewImage,
                        std::string_view normalImage,
                        const Vec2& installedOffset,
                        ui::Widget::TextureResType texType)
{
    if (!Part::init(previewImage, installedOffset, texType))
    {
        return false;
    }

    initNormalTexture(normalImage, texType);
    commonInit();

    return true;
}

void PartOneLayer::setInstalled()
{
    if (_isInstalled)
    {
        return;
    }
    _isInstalled = true;
    _previewSprite->setVisible(false);
    _normalSprite->setVisible(true);
    setContentSize(_normalSprite->getContentSize());
}

void PartOneLayer::setPreview()
{
    if (!_isInstalled)
    {
        return;
    }
    _isInstalled = false;
    _previewSprite->setVisible(true);
    setContentSize(_previewSprite->getContentSize());
    _normalSprite->setVisible(false);
}

void PartOneLayer::setGlobalZOrder(float globalZOrder)
{
    Part::setGlobalZOrder(globalZOrder);
    if (_isInstalled)
    {
        _normalSprite->setGlobalZOrder(globalZOrder);
    }
}

void PartOneLayer::initRenderer()
{
    Part::initRenderer();
    _normalSprite = Sprite::create();
    addChild(_normalSprite);
}

void PartOneLayer::initNormalTexture(std::string_view filename,
                                     ui::Widget::TextureResType texType)
{
    _normalFileName = filename;
    _normalTexType = texType;
    if (_normalSpriteLoaded = !filename.empty();
        _normalSpriteLoaded)
    {
        switch (texType)
        {
        case TextureResType::LOCAL:
            _normalSprite->initWithFile(filename);
            break;
        case TextureResType::PLIST:
            _normalSprite->initWithSpriteFrameName(filename);
            break;
        default:
            break;
        }
    }
}

void PartOneLayer::savePropertiesToJson(JSONBasic* jsonBasic) const
{
    Part::savePropertiesToJson(jsonBasic);
    jsonBasic->setStringForKey(normalFileNameProp, _normalFileName.c_str());
    jsonBasic->setIntegerForKey(normalTexTypeProp, static_cast<int>(_normalTexType));
}

void PartOneLayer::loadPropertiesFromJson(JSONBasic* jsonBasic)
{
    Part::loadPropertiesFromJson(jsonBasic);
    auto normalFileName = jsonBasic->getStringForKey(normalFileNameProp);
    auto normalTexType = static_cast<TextureResType>(jsonBasic->getIntegerForKey(normalTexTypeProp));
    initNormalTexture(normalFileName, normalTexType);
    commonInit();
}

void PartOneLayer::commonInit()
{
    if (_normalSpriteLoaded)
    {
        _normalSprite->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
        _normalSprite->setVisible(false);
    }
    else
    {
        AXLOGERROR("Normal sprite is not loaded!");
    }
}

} // namespace car