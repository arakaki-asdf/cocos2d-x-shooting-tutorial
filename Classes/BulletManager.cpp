
#include "BulletManager.h"
#include "util.h"


bool BulletManager::init() {
  if (!Node::init()) { return false;  }

  bullets_.resize(100);
  for (size_t i = 0; i < bullets_.size(); ++i) {
    auto bullet = util::cricle(util::mid(), 15.0f, Color4F::WHITE);
    bullet->setVisible(false);

    bullets_[i] = bullet;
    addChild(bullets_[i]);
  }

  return true;
}

void BulletManager::update() {
  for (size_t i = 0; i < bullets_.size(); ++i) {
    auto bullet = bullets_[i];

    if (!bullet->isVisible()) { continue; }

    auto pos = bullet->getPosition();

    if (pos.y >= util::size().height) {
      bullet->setVisible(false);
    } else {
      pos.y += BulletManager::SPEED;
    }

    bullet->setPosition(pos);
  }
}

void BulletManager::shot(const Vec2& position) {
  if (!can_shot_) { return; }

  for (size_t i = 0; i < bullets_.size(); ++i) {
    auto bullet = bullets_[i];

    if (bullet->isVisible()) { continue; }

    can_shot_ = false;
    bullet->setVisible(true);
    bullet->setPosition(position);

    auto action1 = DelayTime::create(BulletManager::INTERVAL);
    auto action2 = CallFunc::create([this]() {
      can_shot_ = true;
    });
    auto seq = Sequence::create(action1, action2, NULL);
    this->runAction(seq);

    return;
  }
}

void BulletManager::disable(size_t index) {
  bullets_[index]->setVisible(false);
}

int BulletManager::collision(const Rect& box1) {
  for (size_t i = 0; i < bullets_.size(); ++i) {
    auto bullet = bullets_[i];
    // 生成されていない弾は処理しない
    if (!bullet->isVisible()) { continue; }

    auto bullet_box = bullet->getBoundingBox();

    // 当たり判定
    if (bullet_box.intersectsRect(box1)) { return i; }
  }

  return -1;
}