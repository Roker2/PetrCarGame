#include "GarageScene.h"

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

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}

void GarageScene::update(float delta)
{

}