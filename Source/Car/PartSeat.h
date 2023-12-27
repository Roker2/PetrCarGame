#pragma once

#include "PartOneLayer.h"

namespace car
{

class PartSeat : public PartOneLayer
{
public:
    PartSeat();

    static PartSeat* create(std::string_view previewImage,
                                std::string_view normalImage,
                                const ax::Vec2& installedOffset = ax::Vec2(),
                                ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual PartType getType() const noexcept override;

public:
    size_t comfort;
};

} // namespace car