#include "GarageScene.h"

#include "Car/Frame.h"
#include "Car/PartBodyFront.h"
#include "Car/PartBodyMiddle.h"
#include "Car/PartBodyRear.h"
#include "Car/PartEngine.h"
#include "Car/PartOneLayer.h"
#include "Car/PartSeat.h"
#include "Car/PartGearbox.h"
#include "Car/PartTwoLayer.h"
#include "Controls/DoorButton.h"

USING_NS_AX;

#define LOADING_FROM_JSON 1

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

    auto carFrame = car::Frame::create("thirdPartyContent/parts/frame.png");
    carFrame->setPosition(Vec2(378.f, 185.f));
    this->addChild(carFrame);

    Sprite* leftFrontWheel = Sprite::create("thirdPartyContent/parts/redWheelInstalledLeft.png");
    this->addChild(leftFrontWheel);
    leftFrontWheel->setGlobalZOrder(16.f);
    leftFrontWheel->setPosition(Vec2(288.5f, 138.f));
    Sprite* rightFrontWheel = Sprite::create("thirdPartyContent/parts/redWheelInstalledRight.png");
    this->addChild(rightFrontWheel);
    rightFrontWheel->setGlobalZOrder(0.f);
    rightFrontWheel->setPosition(Vec2(215.5f, 204.5f));

    Sprite* leftRearWheel = Sprite::create("thirdPartyContent/parts/redWheelInstalledLeft.png");
    this->addChild(leftRearWheel);
    leftRearWheel->setGlobalZOrder(16.f);
    leftRearWheel->setPosition(Vec2(515.5f, 155.f));
    Sprite* rightRearWheel = Sprite::create("thirdPartyContent/parts/redWheelInstalledRight.png");
    this->addChild(rightRearWheel);
    rightRearWheel->setGlobalZOrder(0.f);
    rightRearWheel->setPosition(Vec2(442.5f, 221.5f));

#if LOADING_FROM_JSON == 1
    auto simpleEngine = car::PartEngine::createFromJson("thirdPartyContent/parts/simpleEngine.json");
#else
    auto simpleEngine = car::PartEngine::create("thirdPartyContent/parts/simpleEngine.png",
        "thirdPartyContent/parts/simpleEngine.png",
        Vec2(28.f, 31.f),
        "thirdPartyContent/parts/sounds/smallPartsInstall.wav");
    simpleEngine->setName("Simple engine");
    simpleEngine->saveToJson("thirdPartyContent/parts/simpleEngine.json");
#endif
    simpleEngine->SetOnTouchMovingCallback(std::bind(&car::Frame::onPartTouchMoved, carFrame,
        simpleEngine, std::placeholders::_1, std::placeholders::_2));
    this->addChild(simpleEngine);
    simpleEngine->setPosition(simpleEngine->getContentSize() / 2);

    //auto tracktorFront = car::PartBodyFront::create("thirdPartyContent/parts/tracktorFront.png", "thirdPartyContent/garage/parts/tracktorFront.png");
    //tracktorFront->setName("Tracktor front");
    //tracktorFront->SetOnTouchMovingCallback(std::bind(&car::Frame::onPartTouchMoved, carFrame,
    //    tracktorFront, std::placeholders::_1, std::placeholders::_2));
    //this->addChild(tracktorFront);

#if LOADING_FROM_JSON == 1
    auto yellowCarFront = car::PartBodyFront::createFromJson("thirdPartyContent/parts/yellowCarFront.json");
#else
    auto yellowCarFront = car::PartBodyFront::create(
        "thirdPartyContent/parts/yellowCarFront.png",
        "thirdPartyContent/parts/yellowCarFront.png",
        Vec2(52.f, 4.f),
        "thirdPartyContent/parts/sounds/bodyPartsInstall.wav");
    yellowCarFront->setName("Yellow car front");
    yellowCarFront->saveToJson("thirdPartyContent/parts/yellowCarFront.json");
#endif
    yellowCarFront->SetOnTouchMovingCallback(std::bind(&car::Frame::onPartTouchMoved, carFrame,
        yellowCarFront, std::placeholders::_1, std::placeholders::_2));
    this->addChild(yellowCarFront);
    yellowCarFront->setPosition(yellowCarFront->getContentSize() / 2);

    //auto greenSofa = car::PartSeat::create("thirdPartyContent/parts/greenSofaPreview.png", 
    //    "thirdPartyContent/parts/greenSofaInstalled.png");
    //greenSofa->setName("Green sofa");
    //greenSofa->SetOnTouchMovingCallback(std::bind(&car::Frame::onPartTouchMoved, carFrame,
    //    greenSofa, std::placeholders::_1, std::placeholders::_2));
    //this->addChild(greenSofa);

    //auto raceMiddle = car::PartBodyMiddle::create("thirdPartyContent/parts/raceMiddlePreview.png",
    //    "thirdPartyContent/parts/raceMiddleInstalledFront.png",
    //    "thirdPartyContent/parts/raceMiddleInstalledBack.png",
    //    Vec2(94.f, 78.f),
    //    Vec2(15.f, 89.f));
    //this->addChild(raceMiddle);

#if LOADING_FROM_JSON == 1
    auto greenCarMiddle = car::PartBodyMiddle::createFromJson("thirdPartyContent/parts/greenCarMiddle.json");
#else
    auto greenCarMiddle = car::PartBodyMiddle::create("thirdPartyContent/parts/greenCarMiddlePreview.png",
        "thirdPartyContent/parts/greenCarMiddleInstalledFront.png",
        "thirdPartyContent/parts/greenCarMiddleInstalledBack.png",
        Vec2(93.f, 87.f),
        Vec2(98.f, 111.f),
        Vec2(28.f, 29.5f),
        "thirdPartyContent/parts/sounds/bodyPartsInstall.wav");
    greenCarMiddle->saveToJson("thirdPartyContent/parts/greenCarMiddle.json");
#endif
    greenCarMiddle->SetOnTouchMovingCallback(std::bind(&car::Frame::onPartTouchMoved, carFrame,
        greenCarMiddle, std::placeholders::_1, std::placeholders::_2));
    this->addChild(greenCarMiddle);
    greenCarMiddle->setPosition(greenCarMiddle->getContentSize() / 2);

#if LOADING_FROM_JSON == 1
    auto policeBack = car::PartBodyRear::createFromJson("thirdPartyContent/parts/policeBack.json");
#else
    auto policeBack = car::PartBodyRear::create("thirdPartyContent/parts/policeBackPreview.png",
        "thirdPartyContent/parts/policeBackInstalledFront.png",
        "thirdPartyContent/parts/policeBackInstalledBack.png",
        Vec2(130.f, 86.5f),
        Vec2(62.5f, 121.f),
        Vec2(28.5f, 63.f),
        "thirdPartyContent/parts/sounds/bodyPartsInstall.wav");
    policeBack->saveToJson("thirdPartyContent/parts/policeBack.json");
#endif
    policeBack->SetOnTouchMovingCallback(std::bind(&car::Frame::onPartTouchMoved, carFrame,
        policeBack, std::placeholders::_1, std::placeholders::_2));
    this->addChild(policeBack);
    policeBack->setPosition(policeBack->getContentSize() / 2);


#if LOADING_FROM_JSON == 1
    auto redSofa = car::PartSeat::createFromJson("thirdPartyContent/parts/redSofa.json");
#else
    auto redSofa = car::PartSeat::create("thirdPartyContent/parts/redSofa.png", 
        "thirdPartyContent/parts/redSofa.png",
        Vec2(28.f, 28.5f),
        "thirdPartyContent/parts/sounds/smallPartsInstall.wav");
    redSofa->setName("Red sofa");
    redSofa->saveToJson("thirdPartyContent/parts/redSofa.json");
#endif
    redSofa->SetOnTouchMovingCallback(std::bind(&car::Frame::onPartTouchMoved, carFrame,
        redSofa, std::placeholders::_1, std::placeholders::_2));
    this->addChild(redSofa);
    redSofa->setPosition(redSofa->getContentSize() / 2);

#if LOADING_FROM_JSON == 1
    auto fireEngineMiddle = car::PartBodyMiddle::createFromJson("thirdPartyContent/parts/fireEngineMiddle.json");
#else
    auto fireEngineMiddle = car::PartBodyMiddle::create(
        "thirdPartyContent/parts/fireEngineMiddlePreview.png",
        "thirdPartyContent/parts/fireEngineMiddleInstalledFront.png",
        "thirdPartyContent/parts/fireEngineMiddleInstalledBack.png",
        Vec2(10.f, 4.f),
        Vec2(0.f, 1.5f),
        Vec2(65.f, 101.f),
        "thirdPartyContent/parts/sounds/bodyPartsInstall.wav");
    fireEngineMiddle->saveToJson("thirdPartyContent/parts/fireEngineMiddle.json");
#endif
    fireEngineMiddle->SetOnTouchMovingCallback(std::bind(&car::Frame::onPartTouchMoved, carFrame,
        fireEngineMiddle, std::placeholders::_1, std::placeholders::_2));
    this->addChild(fireEngineMiddle);
    fireEngineMiddle->setPosition(fireEngineMiddle->getContentSize() / 2);

#if LOADING_FROM_JSON == 1
    auto volvoFront = car::PartBodyFront::createFromJson("thirdPartyContent/parts/volvoFront.json");
#else
    auto volvoFront = car::PartBodyFront::create(
        "thirdPartyContent/parts/volvoFrontPreview.png",
        "thirdPartyContent/parts/volvoFrontInstalled.png",
        Vec2(67.f, -11.5f),
        "thirdPartyContent/parts/sounds/bodyPartsInstall.wav");
    volvoFront->saveToJson("thirdPartyContent/parts/volvoFront.json");
#endif
    volvoFront->SetOnTouchMovingCallback(std::bind(&car::Frame::onPartTouchMoved, carFrame,
        volvoFront, std::placeholders::_1, std::placeholders::_2));
    this->addChild(volvoFront);
    volvoFront->setPosition(volvoFront->getContentSize() / 2);

#if LOADING_FROM_JSON == 1
    auto simpleGeagbox = car::PartGearbox::createFromJson("thirdPartyContent/parts/simpleGeagbox.json");
#else
    auto simpleGeagbox = car::PartGearbox::create(
        "thirdPartyContent/parts/simpleGearbox.png",
        "thirdPartyContent/parts/simpleGearbox.png",
        Vec2(8.5f, 27.f),
        "thirdPartyContent/parts/sounds/smallPartsInstall.wav");
    simpleGeagbox->saveToJson("thirdPartyContent/parts/simpleGeagbox.json");
#endif
    simpleGeagbox->SetOnTouchMovingCallback(std::bind(&car::Frame::onPartTouchMoved, carFrame,
        simpleGeagbox, std::placeholders::_1, std::placeholders::_2));
    this->addChild(simpleGeagbox);
    simpleGeagbox->setPosition(simpleGeagbox->getContentSize() / 2);

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
