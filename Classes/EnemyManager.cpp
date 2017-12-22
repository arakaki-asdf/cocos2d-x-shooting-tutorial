
#include "EnemyManager.h"
#include "util.h"

USING_NS_CC;

bool EnemyManager::init() {
  if (!Node::init()) { return false; }

  enemys_.resize(50);
  for (size_t i = 0; i < enemys_.size(); ++i) {
    auto enemy = Enemy::create();
    enemy->setVisible(false);
    enemys_[i] = enemy;

    addChild(enemy);
  }

  auto action1 = DelayTime::create(1.0f);
  auto action2 = CallFunc::create([this]() {
    // x軸は真ん中から-200 <= x <= 200の範囲でランダム生成
    // y軸は一番上から
    auto rand = RandomHelper::random_int(-200, 200);
    enable(Vec2(util::mid().x + rand, util::size().height));
    CCLOG("Spawing Enemy");
  });
  auto seq = Sequence::create(action1, action2, NULL);
  auto re = RepeatForever::create(seq);
  this->runAction(re);

  return true;
}

void EnemyManager::update() {
  for (size_t i = 0; i < enemys_.size(); ++i) {
    auto enemy = enemys_[i];
    enemy->update();

    auto pos = enemy->getPosition();
    if (pos.y < 0) {
      enemy->disable();
    }
  }
}

void EnemyManager::enable(const Vec2& position) {
  for (size_t i = 0; i < enemys_.size(); ++i) {
    auto enemy = enemys_[i];
    if (enemy->isVisible()) { continue; }

    enemy->enable(position);
    return;
  }
}

const std::vector<Enemy*>& EnemyManager::getEnemys() {
  return enemys_;
}