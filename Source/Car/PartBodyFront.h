#pragma once

#include "PartOneLayer.h"
#include "PartBodyBase.h"

namespace car
{

class PartBodyFront : public PartOneLayer, public PartBodyBase
{
public:
    PartBodyFront();

    static PartBodyFront* create(std::string_view previewImage,
                                 std::string_view normalImage,
                                 ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual PartType getType() const noexcept override;

public:
    size_t funnyFactor;
};

} // namespace car