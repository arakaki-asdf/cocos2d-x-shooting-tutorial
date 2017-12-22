#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TitleScene : public cocos2d::Scene {
public:
  CREATE_FUNC(TitleScene);

private:
  virtual bool init();
  void update(float dt);

  cocos2d::ui::Button* createButton(const std::string& normal, const std::string& select = "", const std::string& disable = "");
};