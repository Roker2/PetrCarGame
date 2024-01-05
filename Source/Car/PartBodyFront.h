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
                                 const ax::Vec2& installedOffset = ax::Vec2(),
                                 std::string_view installSoundPath = "",
                                 ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);
    static PartBodyFront* createFromJson(std::string_view filename);

    virtual PartType getType() const noexcept override;

public:
    size_t funnyFactor;
};

} // namespace car