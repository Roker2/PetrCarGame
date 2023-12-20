#include "Frame.h"

#include "Part.h"
#include "PartArea.h"

USING_NS_AX;

namespace car
{

Frame::Frame()
    : Sprite()
{
}

Frame* Frame::create(std::string_view filename,
                     ax::PixelFormat format)
{
    Frame* frame = new Frame();
    if (frame->initWithFile(filename, format))
    {
        frame->autorelease();
        return frame;
    }
    AX_SAFE_DELETE(frame);
    return nullptr;
}

bool Frame::initWithFile(std::string_view filename, PixelFormat format)
{
    if (!Sprite::initWithFile(filename, format))
    {
        return false;
    }

    _partAreas.push_back(PartArea(208.f, 161.f, 114.f, 70.f, PartType::Engine, 12.f));
    _partAreas.push_back(PartArea(311.f, 158.f, 122.f, 121.f, PartType::Seat, 8.f));
    _partAreas.push_back(PartArea(165.f, 135.f, 190.f, 144.f, PartType::BodyFront, 14.f));
    _partAreas.push_back(PartArea(277.f, 144.f, 186.f, 176.f, PartType::BodyMiddle, 10.f));
    _partAreas.push_back(PartArea(385.f, 155.f, 220.f, 180.f, PartType::BodyRear, 5.f));
    return true;
}

void Frame::onPartTouchMoved(Part* part, Touch* touch, Event* event)
{
    if (part != nullptr)
    {
        bool isInstalled{ false };
        for (const auto& partArea : _partAreas)
        {
            if (partArea.partTypeEquals(part->getType())
                && partArea.containsPoint(touch->getLocation()))
            {
#if _AX_DEBUG > 0
                AXLOG("Catched \"%s\", set to needed position", part->getName().data());
#endif
                part->setInstalled();
                const auto& contentSize = part->getContentSize();
                part->setPosition(Vec2(partArea.getMinX() + contentSize.x / 2.f,
                    partArea.getMinY() + contentSize.y / 2.f));
                part->setGlobalZOrder(partArea.getZOrder());
                isInstalled = true;
                break;
            }
        }
        // Roker2: refactor it later
        if (!isInstalled)
        {
            part->setPreview();
        }
    }
}

} // namespace car