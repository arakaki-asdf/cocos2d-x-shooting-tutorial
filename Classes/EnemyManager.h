
#pragma once
#include "cocos2d.h"
#include "Enemy.h"

class EnemyManager : public cocos2d::Node {
public:
  CREATE_FUNC(EnemyManager);

private:
  std::vector<Enemy*> enemys_;

public:
  virtual bool init();
  void update();
  void enable(const cocos2d::Vec2& position);
  const std::vector<Enemy*>& getEnemys();
};