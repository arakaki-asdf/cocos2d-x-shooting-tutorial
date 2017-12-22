
#pragma once

#include "cocos2d.h"

class BulletManager : public cocos2d::Node {
public:
  CREATE_FUNC(BulletManager);

private:
  const float INTERVAL = 0.1f;
  const float SPEED = 30.0f;
  std::vector<cocos2d::DrawNode*> bullets_;
  bool can_shot_ = true;

public:
  virtual bool init();
  void update();
  void shot(const cocos2d::Vec2& position);
  // true: -1以外, false: -1
  int collision(const cocos2d::Rect& rect);
  void disable(size_t index);
};