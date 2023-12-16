#pragma once

#include "axmol.h"
#include "ui/UIWidget.h"
#include "PartType.h"

namespace car
{

class Part : public ax::ui::Widget
{
public:
    Part();
    virtual ~Part() = default;

    static Part* create(std::string_view previewImage,
                        ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);
    bool init(std::string_view previewImage,
              ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual PartType getType() const noexcept;

protected:
    virtual void initRenderer() override;

    void initPreviewTexture(std::string_view filename,
                            ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

private:
    // touch
    bool onTouchBegan(ax::Touch* touch, ax::Event* event) override;
    void onTouchMoved(ax::Touch* touch, ax::Event* event) override;
    void onTouchEnded(ax::Touch* touch, ax::Event* event) override;

protected:
    ax::Sprite* _previewSprite;

    bool _previewSpriteLoaded;

    std::string _previewFileName;
    ax::ui::Widget::TextureResType _previewTexType;
};

} // namespace car