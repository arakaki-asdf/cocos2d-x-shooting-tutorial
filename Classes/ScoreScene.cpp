
#include "ScoreScene.h"
#include "TitleScene.h"
#include "util.h"

bool ScoreScene::init() {
  if (!Scene::init()) { return false; }

  auto load = UserDefault::getInstance();
  auto score = load->getIntegerForKey("score");
  auto score_label = util::label(util::strFormat("score %d", score), 50, Vec2(util::mid().x, util::mid().y + 60));
  addChild(score_label);

  auto label = util::label("BACK TITLE", 30, Vec2(util::mid().x, util::mid().y - 10));
  addChild(label);

  auto button = util::button("btn_02.png");
  button->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
      Director::getInstance()->replaceScene(TransitionSlideInR::create(0.35f, TitleScene::create()));
    }
  });
  addChild(button);

  this->scheduleUpdate();

  return true;
}

void ScoreScene::update(float dt) {
  CCLOG("UPDATE");
}