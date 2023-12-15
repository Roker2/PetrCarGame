#include "Frame.h"

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

} // namespace car