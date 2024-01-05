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
                                const ax::Vec2& installedOffset = ax::Vec2(),
                                std::string_view installSoundPath = "",
                                ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);
    static PartOneLayer* createFromJson(std::string_view filename);
    bool init(std::string_view previewImage,
              std::string_view normalImage,
              const ax::Vec2& installedOffset = ax::Vec2(),
              std::string_view installSoundPath = "",
              ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual void setInstalled() override;
    virtual void setPreview() override;
    virtual void setGlobalZOrder(float globalZOrder) override;

protected:
    virtual void initRenderer() override;

    void initNormalTexture(std::string_view filename,
                           ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual void savePropertiesToJson(ax::extension::JSONBasic* jsonBasic) const override;
    virtual void loadPropertiesFromJson(ax::extension::JSONBasic* jsonBasic) override;

private:
    void commonInit();

protected:
    ax::Sprite* _normalSprite;

    bool _normalSpriteLoaded;

    std::string _normalFileName;
    ax::ui::Widget::TextureResType _normalTexType;
};

} // namespace car