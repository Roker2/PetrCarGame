#include "GarageScene.h"

#include "Controls/DoorButton.h"

USING_NS_AX;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf(
        "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
        "MainScene.cpp\n");
}

bool GarageScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto backgroundSprite = Sprite::create("thirdPartyContent/garage/background.png");
    if (backgroundSprite == nullptr)
    {
        problemLoading("'thirdPartyContent/garage/background.png'");
    }
    else
    {
        const auto safeArea = _director->getSafeAreaRect();
        const auto& safeOrigin = safeArea.origin;
        const auto& mapSpriteSize = safeArea.size;
        backgroundSprite->setContentSize(mapSpriteSize);
        backgroundSprite->setPosition(Vec2(mapSpriteSize.x / 2 + safeOrigin.x, mapSpriteSize.y / 2 + safeOrigin.y));
        this->addChild(backgroundSprite, 0);
    }

    auto yellowDoor = createDoor("thirdPartyContent/garage/YellowDoorClosed.png", "thirdPartyContent/garage/YellowDoorOpened.png", Vec2(474.f, 468.f));
    this->addChild(yellowDoor);

    auto gates = createDoor("thirdPartyContent/garage/GatesClosed.png", "thirdPartyContent/garage/GatesOpened.png", Vec2(-4.f, 458.f));
    this->addChild(gates);

    auto greenDoor = createDoor("thirdPartyContent/garage/GreenDoorClosed.png", "thirdPartyContent/garage/GreenDoorOpened.png", Vec2(70.f, 455.f));
    this->addChild(greenDoor);

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}

void GarageScene::update(float delta)
{

}

DoorButton* GarageScene::createDoor(std::string_view normalImage,
                       std::string_view hoverImage,
                       const ax::Vec2& pos)
{
    auto doorBtn = DoorButton::create(normalImage, hoverImage);
    doorBtn->setPosition(Vec2(pos.x + doorBtn->getContentSize().x / 2, pos.y - doorBtn->getContentSize().y / 2));
    return doorBtn;
}
