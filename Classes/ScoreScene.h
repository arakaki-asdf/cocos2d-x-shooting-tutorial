
#pragma once
#include "cocos2d.h"

class ScoreScene : public cocos2d::Scene {
public:
  CREATE_FUNC(ScoreScene);

private:
  virtual bool init();
  void update(float dt);
};