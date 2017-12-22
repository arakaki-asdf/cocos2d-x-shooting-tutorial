
#pragma once

#include "cocos2d.h"
#include "BulletManager.h"
#include "EnemyManager.h"

class GameScene : public cocos2d::Scene {
public:
  CREATE_FUNC(GameScene);

private:
  cocos2d::Vec2 touch_position_;
  cocos2d::DrawNode* player_;
  BulletManager* bullet_manager_;
  EnemyManager* enemy_manager_;
  bool is_touch_display_;

  const float TIME_LIMIT = 10.0f;

  // timer
  float timer_ = 0.0f;
  cocos2d::Label* timer_label_;

  // score
  int score_ = 0;
  cocos2d::Label* score_label_;

private:
  virtual bool init();
  virtual void update(float dt);
  virtual void onEnterTransitionDidFinish();

  virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
  void shot();
  void collision(EnemyManager* enemy_manager, BulletManager* bullet_manager);
  void timerUpdate(float dt);
};