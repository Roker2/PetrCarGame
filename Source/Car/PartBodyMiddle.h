#pragma once

#include "PartTwoLayer.h"
#include "PartBodyBase.h"

namespace car
{

class PartBodyMiddle : public PartTwoLayer, public PartBodyBase
{
public:
    PartBodyMiddle();
    virtual ~PartBodyMiddle() = default;

    static PartBodyMiddle* create(std::string_view previewImage,
        std::string_view normalFrontImage,
        std::string_view normalBackImage,
        const ax::Vec2& frontImagePos,
        const ax::Vec2& backImagePos,
        ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual PartType getType() const noexcept override;
};

} // namespace car