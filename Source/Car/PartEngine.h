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
                              ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual PartType getType() const noexcept override;

public:
    size_t speed;
    size_t fuelConsumption;
    size_t strength;
};

} // namespace car