#include "PartOneLayer.h"

USING_NS_AX;

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
                                   ui::Widget::TextureResType texType)
{
    PartOneLayer* part = new PartOneLayer();
    if (part->init(previewImage, normalImage, texType))
    {
        part->autorelease();
        return part;
    }
    AX_SAFE_DELETE(part);
    return nullptr;
}

bool PartOneLayer::init(std::string_view previewImage,
                        std::string_view normalImage,
                        ui::Widget::TextureResType texType)
{
    if (!Part::init(previewImage, texType))
    {
        return false;
    }

    initNormalTexture(normalImage, texType);
    _normalSprite->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);

    return true;
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

} // namespace car