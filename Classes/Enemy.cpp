
#include "Enemy.h"
#include "util.h"

USING_NS_CC;

bool Enemy::init() {
  if (!Node::init()) { return false; }

  draw_node_ = util::reverseTriangle(Vec2::ZERO, Size(80, 80), Color4F::ORANGE);
  addChild(draw_node_);
  setContentSize(Size(80, 80));
  type_ = Type::Straight;

  return true;
}

void Enemy::enable(const Vec2& position) {
  life_ = Enemy::LIFE;
  setVisible(true);
  setPosition(position);
}

void Enemy::disable() {
  setVisible(false);
  setPosition(Vec2::ZERO);
}

void Enemy::update() {
  // 死亡しているなら、処理しない
  if (!this->isVisible()) { return; }

  // 敵タイプによって動作変更を想定
  switch (type_) {
  case Type::Straight: straight(); break;
  }
}

// 下へ進む
void Enemy::straight() {
  auto pos = getPosition();
  pos.x -= 0;
  pos.y -= 10;
  setPosition(pos);
}

void Enemy::onCollision() {
  CCLOG("life %d", life_);
  life_ -= 1;
  if (life_ <= 0) { disable(); }
}