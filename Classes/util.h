
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class util {
public:
  static Vec2 mid() {
    auto size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    return Vec2(size.width / 2 + origin.x, size.height / 2 + origin.y);
  }

  static Size size() {
    return Director::getInstance()->getVisibleSize();
  }

  static DrawNode* triangle(const Vec2& position, const Size& size, const Color4F& color) {
    auto node = DrawNode::create();
    node->drawTriangle(Vec2::ZERO, Vec2(size.width / 2, size.height), Vec2(size.width, 0), color);
    node->setPosition(position);
    return node;
  }
  static DrawNode* cricle(const Vec2& position, float radius, const Color4F& color) {
    auto node = DrawNode::create();
    node->drawDot(Vec2::ZERO, radius, color);
    node->setPosition(position);
    return node;
  }
  static DrawNode* reverseTriangle(const Vec2& position, const Size& size, const Color4F& color) {
    auto node = DrawNode::create();
    node->drawTriangle(Vec2(0, size.height), Vec2(size.width / 2, 0), Vec2(size.width, size.height), color);
    node->setPosition(position);

    return node;
  }
  template <typename ... Args>
  static std::string strFormat(const char* format, Args const & ... args) {
    static char _buf[256];
    snprintf(_buf, sizeof(_buf), format, args ...);
    return std::string(_buf);
  }

  static Label* label(const std::string& text, float fontSize, const Vec2& position) {
    auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", fontSize);
    label->setPosition(position);
    return label;
  }

  static cocos2d::ui::Button* button(const std::string& normal, const std::string& select = "", const std::string& disable = "") {
    auto button = ui::Button::create();
    button->setTouchEnabled(true);
    button->loadTextures(normal, select, disable);
    button->setPosition(Vec2(util::mid().x, 100));

    return button;
  }
};