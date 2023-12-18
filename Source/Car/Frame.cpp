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

    _partAreas.push_back(PartArea(256.f, 167.f, 77.f, 35.f, PartType::Engine));
    return true;
}

void Frame::onPartTouchMoved(Part* part, Touch* touch, Event* event)
{
    if (part->getName().empty())
        return;
    AXLOG(part->getName().data());
}

} // namespace car