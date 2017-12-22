
#include "TitleScene.h"
#include "GameScene.h"
#include "util.h"

USING_NS_CC;

bool TitleScene::init() {
  if (!Scene::init()) { return false; }

  this->scheduleUpdate();

  createButton("btn_01.png");

  return true;
}

void TitleScene::update(float dt) {
  CCLOG("UPDATE");
}

cocos2d::ui::Button* TitleScene::createButton(const std::string& normal, const std::string& select, const std::string& disable) {
  auto button = ui::Button::create();
  button->setTouchEnabled(true);
  button->loadTextures(normal, select, disable);
  button->setPosition(Vec2(util::mid().x, 100));

  button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
      Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f, GameScene::create()));
    }
  });

  addChild(button);

  return button;
}
