#pragma once

#include "PartOneLayer.h"

namespace car
{

class PartGearbox : public PartOneLayer
{
public:
    PartGearbox();

    static PartGearbox* create(std::string_view previewImage,
        std::string_view normalImage,
        const ax::Vec2& installedOffset = ax::Vec2(),
        std::string_view installSoundPath = "",
        ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);
    static PartGearbox* createFromJson(std::string_view filename);

    virtual PartType getType() const noexcept override;

public:
    size_t acceleration;
};

} // namespace car