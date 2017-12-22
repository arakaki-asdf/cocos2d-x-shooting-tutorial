
#include "GameScene.h"
#include "ScoreScene.h"
#include "ui/CocosGUI.h"
#include "util.h"

USING_NS_CC;

bool GameScene::init() {
  if (!Scene::init()) { return false; }

  player_ = util::triangle(Vec2(util::mid().x, 120), Size(50, 50), Color4F::BLUE);
  player_->setContentSize(Size(50, 50));
  addChild(player_);

  bullet_manager_ = BulletManager::create();
  addChild(bullet_manager_);

  enemy_manager_ = EnemyManager::create();
  addChild(enemy_manager_);

  timer_ = GameScene::TIME_LIMIT;
  timer_label_ = util::label("", 24, Vec2(50, util::size().height - 20));
  addChild(timer_label_);

  score_ = 0;
  score_label_ = util::label("", 24, Vec2(50, util::size().height - 60));
  addChild(score_label_);

  is_touch_display_ = false;

  auto listener = EventListenerTouchOneByOne::create();
  listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
  listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
  listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

  _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

  return true;
}

void GameScene::update(float dt) {
  timerUpdate(dt);

  if (is_touch_display_) {
    shot();
  }

  bullet_manager_->update();
  enemy_manager_->update();

  collision(enemy_manager_, bullet_manager_);
}
void GameScene::timerUpdate(float dt) {
  timer_ -= dt;
  timer_ = MAX(timer_, 0.0f);

  if (timer_ <= 0.0f) {
    unscheduleUpdate();
    auto save = UserDefault::getInstance();
    save->setIntegerForKey("score", score_);
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, ScoreScene::create()));
  }

  timer_label_->setString(util::strFormat("timer %.2f", timer_));
}

void GameScene::shot() {
  auto pos = Vec2(player_->getPosition().x + player_->getContentSize().width / 2, player_->getPosition().y + player_->getContentSize().height);
  bullet_manager_->shot(pos);
}

void GameScene::onEnterTransitionDidFinish() {
  this->scheduleUpdate();
}

bool GameScene::onTouchBegan(Touch* touch, Event* event) {
  touch_position_ = touch->getLocation();
  is_touch_display_ = true;
  return true;
}
void GameScene::onTouchMoved(Touch* touch, Event* event) {
  auto diff_position = touch->getLocation() - touch_position_;
  touch_position_ = touch->getLocation();
  player_->setPosition(player_->getPosition() + diff_position);
}

void GameScene::onTouchEnded(Touch* touch, Event* event) {
  is_touch_display_ = false;
}

void GameScene::collision(EnemyManager* enemy_manager, BulletManager* bullet_manager) {
  auto enemys = enemy_manager->getEnemys();
  for (size_t i = 0; i < enemys.size(); ++i) {
    auto enemy = enemys[i];
    auto enemy_box = enemy->getBoundingBox();

    int bullet_index = bullet_manager->collision(enemy_box);

    if (bullet_index != -1) {
      // 弾を非表示
      bullet_manager->disable(bullet_index);

      // 敵衝突処理
      enemy->onCollision();

      // スコア加算
      score_ += 12;
      score_label_->setString(util::strFormat("score %d", score_));
    }
  }
}