#pragma once

#include "Part.h"

namespace car
{

class PartTwoLayer : public Part
{
public:
    PartTwoLayer();
    virtual ~PartTwoLayer() = default;

    static PartTwoLayer* create(std::string_view previewImage,
                                std::string_view normalFrontImage,
                                std::string_view normalBackImage,
                                const ax::Vec2& frontImagePos,
                                const ax::Vec2& backImagePos,
                                ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);
    bool init(std::string_view previewImage,
              std::string_view normalFrontImage,
              std::string_view normalBackImage,
              const ax::Vec2& frontImagePos,
              const ax::Vec2& backImagePos,
              ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual void setInstalled() override;
    virtual void setPreview() override;
    virtual void setGlobalZOrder(float globalZOrder) override;

protected:
    virtual void initRenderer() override;
    
    void initNormalFrontTexture(std::string_view filename,
                                ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);
    void initNormalBackTexture(std::string_view filename,
                               ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

protected:
    ax::Sprite* _normalFrontSprite;
    ax::Sprite* _normalBackSprite;

    bool _normalFrontSpriteLoaded;
    bool _normalBackSpriteLoaded;

    std::string _normalFrontFileName;
    std::string _normalBackFileName;
    ax::ui::Widget::TextureResType _normalFrontTexType;
    ax::ui::Widget::TextureResType _normalBackTexType;
    ax::Vec2 _normalContentSize;
    ax::Vec2 _backImageOffset;
};

} // namespace car