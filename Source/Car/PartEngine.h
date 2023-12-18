#pragma once

#include "PartOneLayer.h"

namespace car
{

class PartEngine : public PartOneLayer
{
public:
    static PartEngine* create(std::string_view previewImage,
                              std::string_view normalImage,
                              ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual PartType getType() const noexcept override;
};

} // namespace car