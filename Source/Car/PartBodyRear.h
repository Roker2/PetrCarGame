#pragma once

#include "PartTwoLayer.h"
#include "PartBodyBase.h"

namespace car
{

class PartBodyRear : public PartTwoLayer, public PartBodyBase
{
public:
    PartBodyRear();
    virtual ~PartBodyRear() = default;

    static PartBodyRear* create(std::string_view previewImage,
        std::string_view normalFrontImage,
        std::string_view normalBackImage,
        const ax::Vec2& frontImagePos,
        const ax::Vec2& backImagePos,
        ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual PartType getType() const noexcept override;
};

} // namespace car