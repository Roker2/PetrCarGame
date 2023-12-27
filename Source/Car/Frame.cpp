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

    _partAreas.push_back(PartArea(237.f, 165.f, 73.f, 81.f, PartType::Engine, 12.f));
    _partAreas.push_back(PartArea(360.f, 186.f, 72.f, 103.f, PartType::Seat, 8.f));
    _partAreas.push_back(PartArea(207.f, 202.f, 190.f, 54.f, PartType::BodyFront, 14.f));
    _partAreas.push_back(PartArea(342.f, 202.f, 49.f, 128.f, PartType::BodyMiddle, 10.f));
    _partAreas.push_back(PartArea(465.f, 181.f, 49.f, 125.f, PartType::BodyRear, 5.f));
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
                part->setPosition(Vec2(partArea.getMinX() + part->getInstalledOffset().x,
                    partArea.getMinY() + part->getInstalledOffset().y));
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