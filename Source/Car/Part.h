#pragma once

#include "axmol.h"
#include "ui/UIWidget.h"
#include "rapidjson/document.h"
#include "PartType.h"

namespace ax::extension
{
    class JSONBasic;
} // namespace ax::extension

namespace car
{

class Part : public ax::ui::Widget
{
    using onTouchMovingCallback = std::function<void(ax::Touch*, ax::Event*)>;

public:
    Part();
    virtual ~Part() = default;

    static Part* create(std::string_view previewImage,
                        const ax::Vec2& installedOffset = ax::Vec2(),
                        ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);
    bool init(std::string_view previewImage,
              const ax::Vec2& installedOffset = ax::Vec2(),
              ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    void SetOnTouchMovingCallback(onTouchMovingCallback callback) noexcept;

    virtual PartType getType() const noexcept;
    virtual void setInstalled();
    virtual void setPreview();
    bool getIsInstalled() const noexcept;
    const ax::Vec2& getInstalledOffset() const noexcept;

    void saveToJson(std::string_view filename) const;
    void loadFromJson(std::string_view filename);

protected:
    virtual void initRenderer() override;

    void initPreviewTexture(std::string_view filename,
                            ax::ui::Widget::TextureResType texType = TextureResType::LOCAL);

    virtual void savePropertiesToJson(ax::extension::JSONBasic* jsonBasic) const;
    virtual void loadPropertiesFromJson(ax::extension::JSONBasic* jsonBasic);

private:
    // touch
    bool onTouchBegan(ax::Touch* touch, ax::Event* event) override;
    void onTouchMoved(ax::Touch* touch, ax::Event* event) override;
    void onTouchEnded(ax::Touch* touch, ax::Event* event) override;

public:
    size_t weight;

protected:
    ax::Sprite* _previewSprite;

    bool _previewSpriteLoaded;

    std::string _previewFileName;
    ax::ui::Widget::TextureResType _previewTexType;

    onTouchMovingCallback _onTouchMovingCallback;
    bool _isInstalled;
    ax::Vec2 _installedOffset;
};

} // namespace car