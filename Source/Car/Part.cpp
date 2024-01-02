#include "Part.h"
#include "JSONDefault/JSONBasic.h"
#include <iostream>
#include <fstream>

USING_NS_AX;
USING_NS_AX_EXT;

namespace
{
const char* previewFileNameProp = "previewFileName";
const char* previewTexTypeProp = "previewTexType";
const char* installedOffsetXProp = "installedOffsetX";
const char* installedOffsetYProp = "installedOffsetY";
const char* partTypeProp = "partType";
const char* partNameProp = "partName";
} // namespace

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

Part* Part::createFromJson(std::string_view filename)
{
    Part* part = new Part();
    if (part->loadFromJson(filename))
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
    _installedOffset = installedOffset;
    commonInit();

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

void Part::saveToJson(std::string_view filename) const
{
    if (!FileUtils::getInstance()->isFileExist(filename))
    {
        std::ofstream outfile(filename.data());
        outfile << "{}" << std::endl;
        outfile.close();
    }
    auto jsonBasic = new JSONBasic(FileUtils::getInstance()->fullPathForFilename(filename));
    savePropertiesToJson(jsonBasic);
    jsonBasic->flush();
    AX_SAFE_DELETE(jsonBasic);
}

bool Part::loadFromJson(std::string_view filename)
{
    if (!Widget::init())
    {
        return false;
    }
    if (FileUtils::getInstance()->isFileExist(filename))
    {
        auto jsonBasic = new JSONBasic(FileUtils::getInstance()->fullPathForFilename(filename));
        loadPropertiesFromJson(jsonBasic);
        return true;
    }
    else
    {
        AXLOGERROR("Path %s not exist", filename.data());
        return false;
    }
}

void Part::initRenderer()
{
    Widget::initRenderer();
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

void Part::savePropertiesToJson(JSONBasic* jsonBasic) const
{
    jsonBasic->setStringForKey(previewFileNameProp, _previewFileName.c_str());
    jsonBasic->setIntegerForKey(previewTexTypeProp, static_cast<int>(_previewTexType));
    jsonBasic->setFloatForKey(installedOffsetXProp, _installedOffset.x);
    jsonBasic->setFloatForKey(installedOffsetYProp, _installedOffset.y);
    jsonBasic->setIntegerForKey(partTypeProp, static_cast<int>(getType()));
    jsonBasic->setStringForKey(partNameProp, getName().data());
}

void Part::loadPropertiesFromJson(JSONBasic* jsonBasic)
{
    auto previewFileName = jsonBasic->getStringForKey(previewFileNameProp);
    auto previewTexType = static_cast<TextureResType>(jsonBasic->getIntegerForKey(previewTexTypeProp));
    _installedOffset.x = jsonBasic->getFloatForKey(installedOffsetXProp);
    _installedOffset.y = jsonBasic->getFloatForKey(installedOffsetYProp);
    initPreviewTexture(previewFileName, previewTexType);
    setName(jsonBasic->getStringForKey(partNameProp, ""));
    commonInit();
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
        setPosition(touch->getLocation());
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

void Part::commonInit()
{
    if (_previewSpriteLoaded)
    {
        setContentSize(_previewSprite->getContentSize());
        _previewSprite->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
    }
    else
    {
        AXLOGERROR("Preview sprite is not loaded!");
    }
}

} // namespace car