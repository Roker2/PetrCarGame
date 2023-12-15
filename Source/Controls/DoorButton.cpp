#include "DoorButton.h"

#include "ui/UIScale9Sprite.h"

USING_NS_AX;

DoorButton::DoorButton()
	: ax::ui::Button()
	, _hoverFileName("")
{

}

DoorButton* DoorButton::create(std::string_view normalImage,
                               std::string_view hoverImage,
                               TextureResType texType)
{
    DoorButton* btn = new DoorButton;
    if (btn->init(normalImage, hoverImage, texType))
    {
        btn->autorelease();
        return btn;
    }
    AX_SAFE_DELETE(btn);
    return nullptr;
}

bool DoorButton::init(std::string_view normalImage,
                      std::string_view hoverImage,
                      TextureResType texType)
{
    _hoverFileName = hoverImage;
    return Button::init(normalImage, normalImage, normalImage, texType);
}