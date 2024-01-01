#pragma once

#include "PartOneLayer.h"

namespace car
{

class PartEngine : public PartOneLayer
{
public:
    PartEngine();

    static PartEngine* create(std::string_view previewImage,
                              std::string_view normalImage,
                              const ax::Vec2& installedOffset = ax::Vec2(),
                              ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);
    static PartEngine* createFromJson(std::string_view filename);

    virtual PartType getType() const noexcept override;

public:
    size_t speed;
    size_t fuelConsumption;
    size_t strength;
};

} // namespace car