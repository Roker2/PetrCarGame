#include "DoorButton.h"

USING_NS_AX;

DoorButton::DoorButton()
	: ax::ui::Button()
	, _hoverFileName("")
{

}

DoorButton* DoorButton::create(std::string_view normalImage = "",
                               std::string_view hoverImage  = "",
                               TextureResType texType       = TextureResType::LOCAL)
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

bool DoorButton::init(std::string_view normalImage = "",
                      std::string_view hoverImage = "",
                      TextureResType texType = TextureResType::LOCAL)
{
    _hoverFileName = hoverImage;
    return Button::init(normalImage, normalImage, normalImage, texType);
}