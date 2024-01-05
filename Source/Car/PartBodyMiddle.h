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
        const ax::Vec2& installedOffset = ax::Vec2(),
        std::string_view installSoundPath = "",
        ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);
    static PartBodyMiddle* createFromJson(std::string_view filename);

    virtual PartType getType() const noexcept override;
};

} // namespace car