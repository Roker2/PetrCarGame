#pragma once

#include "Part.h"

namespace car
{

class PartOneLayer : public Part
{
public:
    PartOneLayer();
    virtual ~PartOneLayer() = default;

    static PartOneLayer* create(std::string_view previewImage,
                                std::string_view normalImage,
                                ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);
    bool init(std::string_view previewImage,
              std::string_view normalImage,
              ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual void setInstalled() override;
    virtual void setPreview() override;
    virtual void setGlobalZOrder(float globalZOrder) override;

protected:
    virtual void initRenderer() override;

    void initNormalTexture(std::string_view filename,
                           ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

protected:
    ax::Sprite* _normalSprite;

    bool _normalSpriteLoaded;

    std::string _normalFileName;
    ax::ui::Widget::TextureResType _normalTexType;
};

} // namespace car