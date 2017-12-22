#pragma once
#include "cocos2d.h"

class Enemy : public cocos2d::Node {
public:
  CREATE_FUNC(Enemy);

public:
  enum Type{
    Straight, // 直線移動タイプ
  };

private:
  const int LIFE = 3;
  Type type_;
  cocos2d::DrawNode* draw_node_;
  int life_;

public:
  virtual bool init();
  void enable(const cocos2d::Vec2& position);
  void disable();
  void update();
  void straight();
  void onCollision();
};