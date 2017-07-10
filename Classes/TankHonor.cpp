#include "TankHonor.hpp"

Scene* TankHonor::createScene() {
    auto scene = Scene::create();
    auto layer = TankHonor::create();
    scene->addChild(layer);
    return scene;
}

bool TankHonor::init() {
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    timer = 0;
    
	addSprites();     // 添加背景和各种精灵
	addListeners();   // 添加监听器
	addSchedulers();  // 添加定时调度器
    
    preloadMusic();   // 预加载音效
    loadAnimation();  // 预加载动画帧
    
    return true;
}

void TankHonor::addSprites() {
	// 添加地图
	auto bg = Sprite::create("pictures/map.png");
	bg->setPosition(visibleSize / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);

	// 添加坦克精灵
	// 红队
	Tank* RTank0 = Tank::create(true, FIGHTER);
	Tank* RTank1 = Tank::create(true, ASSASSIN);
	Tank* RTank2 = Tank::create(true, SHOOTER);
    labels[RTank0] = createHealthValueLabel();
    labels[RTank1] = createHealthValueLabel();
    labels[RTank2] = createHealthValueLabel();
    
	RTank0->setPosition(Vec2(200.0f, visibleSize.height / 2 + 100.0f));
    labels[RTank0]->setPosition(RTank0->getPosition() + Vec2(0.0f, 40.0f));
	RTank1->setPosition(Vec2(200.0f, visibleSize.height / 2));
    labels[RTank1]->setPosition(RTank1->getPosition() + Vec2(0.0f, 40.0f));
	RTank2->setPosition(Vec2(200.0f, visibleSize.height / 2 - 100.0f));
    labels[RTank2]->setPosition(RTank2->getPosition() + Vec2(0.0f, 40.0f));
	RTank0->setContentSize(Size(70, 70));
	RTank1->setContentSize(Size(70, 70));
	RTank2->setContentSize(Size(70, 70));
	playerTeam1.push_back(RTank0);
	playerTeam1.push_back(RTank1);
	playerTeam1.push_back(RTank2);
	this->addChild(RTank0, 2);
    this->addChild(labels[RTank0], 2);
	this->addChild(RTank1, 2);
    this->addChild(labels[RTank1], 2);
	this->addChild(RTank2, 2);
    this->addChild(labels[RTank2], 2);

	// 交付控制权
	player1 = RTank0;

	// 蓝队
	Tank* BTank0 = Tank::create(false, FIGHTER);
	Tank* BTank1 = Tank::create(false, ASSASSIN);
	Tank* BTank2 = Tank::create(false, SHOOTER);
    labels[BTank0] = createHealthValueLabel();
    labels[BTank1] = createHealthValueLabel();
    labels[BTank2] = createHealthValueLabel();
	BTank0->setPosition(Vec2(visibleSize.width - 200.0f, visibleSize.height / 2 + 100.0f));
    labels[BTank0]->setPosition(BTank0->getPosition() + Vec2(0.0f, 40.0f));
	BTank1->setPosition(Vec2(visibleSize.width - 200.0f, visibleSize.height / 2));
    labels[BTank1]->setPosition(BTank1->getPosition() + Vec2(0.0f, 40.0f));
	BTank2->setPosition(Vec2(visibleSize.width - 200.0f, visibleSize.height / 2 - 100.0f));
    labels[BTank2]->setPosition(BTank2->getPosition() + Vec2(0.0f, 40.0f));
	// BTank0->setContentSize(Size(70, 70));
	// BTank1->setContentSize(Size(70, 70));
	// BTank2->setContentSize(Size(70, 70));
	playerTeam2.push_back(BTank0);
	playerTeam2.push_back(BTank1);
	playerTeam2.push_back(BTank2);
	this->addChild(BTank0, 2);
    this->addChild(labels[BTank0], 2);
	this->addChild(BTank1, 2);
    this->addChild(labels[BTank1], 2);
	this->addChild(BTank2, 2);
    this->addChild(labels[BTank2], 2);

	// 交付控制权
	player2 = BTank0;
    
    // R基地
    tower1 = Tower::create(true);
    labels[tower1] = createHealthValueLabel();
    tower1->setPosition(Vec2(70, visibleSize.height / 2));
    labels[tower1]->setPosition(tower1->getPosition() + Vec2(0.0f, 90.0f));
    // tower1->setContentSize(Size(180, 180));
    addChild(tower1, 2);
    addChild(labels[tower1], 2);
    base1 = Base::create(true);
    labels[base1] = createHealthValueLabel();
    base1->setPosition(Vec2(50, visibleSize.height / 2));
    labels[base1]->setPosition(base1->getPosition() + Vec2(0.0f, 45.0f));
    // base1->setContentSize(Size(80, 80));
    addChild(base1, 2);
    addChild(labels[base1], 2);
    
    // B基地
    tower2 = Tower::create(false);
    labels[tower2] = createHealthValueLabel();
    tower2->setPosition(Vec2(visibleSize.width - 70.0f, visibleSize.height / 2));
    labels[tower2]->setPosition(tower2->getPosition() + Vec2(0.0f, 90.0f));
    // tower2->setContentSize(Size(180, 180));
    addChild(tower2, 2);
    addChild(labels[tower2], 2);
    base2 = Base::create(false);
    labels[base2] = createHealthValueLabel();
    base2->setPosition(Vec2(visibleSize.width - 50.0f, visibleSize.height / 2));
    labels[base2]->setPosition(base2->getPosition() + Vec2(0.0f, 45.0f));
    // base2->setContentSize(Size(80, 80));
    addChild(base2, 2);
    addChild(labels[base2], 2);

	// 墙实例
	wall = Wall::create();
	wall->setPosition(Vec2(visibleSize.width / 2, 180.0f));
    wall->setContentSize(Size(40, 140));
	this->addChild(wall);
    
    // 大龙和小龙
    big_dragon = Dragon::create(true);
    labels[big_dragon] = createHealthValueLabel();
    big_dragon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 60.0f));
    labels[big_dragon]->setPosition(big_dragon->getPosition() + Vec2(0.0f, 55.0f));
    // big_dragon->setContentSize(Size(100.0f, 100.0f));
    addChild(big_dragon, 2);
    addChild(labels[big_dragon], 2);
    small_dragon = Dragon::create(false);
    labels[small_dragon] = createHealthValueLabel();
    small_dragon->setPosition(Vec2(visibleSize.width / 2, 60.0f));
    labels[small_dragon]->setPosition(small_dragon->getPosition() + Vec2(0.0f, 55.0f));
    // small_dragon->setContentSize(Size(100.0f, 100.0f));
    addChild(small_dragon, 2);
    addChild(labels[small_dragon], 2);
}

void TankHonor::preloadMusic() {
    auto sae = SimpleAudioEngine::getInstance();
    
    //// 加载音效
    sae->preloadEffect("sounds/fire.mp3");
    sae->preloadEffect("sounds/boom.mp3");
    sae->preloadEffect("sounds/gameover.mp3");
    sae->preloadEffect("sounds/R-comeon.mp3");
    sae->preloadEffect("sounds/B-comeon.mp3");
    
    // 播放背景音乐
    sae->preloadBackgroundMusic("sounds/bgm.mp3");
    sae->playBackgroundMusic("sounds/bgm.mp3", true);
}

void TankHonor::addListeners() {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(TankHonor::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(TankHonor::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void TankHonor::loadAnimation() {
    char filename[50];
    
    Vector<SpriteFrame*> R_bullet_destroy;
    Vector<SpriteFrame*> B_bullet_destroy;
	Vector<SpriteFrame*> B_assassin_destroy;
	Vector<SpriteFrame*> R_assassin_destroy;
	Vector<SpriteFrame*> B_base_destroy;
    Vector<SpriteFrame*> R_tower_destroy;
	Vector<SpriteFrame*> R_base_destroy;
    Vector<SpriteFrame*> B_tower_destroy;
	Vector<SpriteFrame*> B_fighter_destroy;
	Vector<SpriteFrame*> R_fighter_destroy;
	Vector<SpriteFrame*> B_shooter_destroy;
	Vector<SpriteFrame*> R_shooter_destroy;
	Vector<SpriteFrame*> big_dragon_destroy;
	Vector<SpriteFrame*> small_dragon_destroy;

    // 大龙爆炸
	for (int i = 1; i <= 6; i++) {
		sprintf(filename, "pictures/big-dragon-destroy-%d.png", i);
		auto image = Director::getInstance()->getTextureCache()->addImage(filename);
		auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 80, 80)));
		big_dragon_destroy.pushBack(frame);
	}
	Animation* animation1 = Animation::createWithSpriteFrames(big_dragon_destroy, 0.1f);
	AnimationCache::getInstance()->addAnimation(animation1, "big-dragon-destroy");

    // 小龙爆炸
	for (int i = 1; i <= 6; i++) {
		sprintf(filename, "pictures/small-dragon-destroy-%d.png", i);
		auto image = Director::getInstance()->getTextureCache()->addImage(filename);
		auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 80, 80)));
		small_dragon_destroy.pushBack(frame);
	}
	Animation* animation2 = Animation::createWithSpriteFrames(small_dragon_destroy, 0.1f);
	AnimationCache::getInstance()->addAnimation(animation2, "small-dragon-destroy");

    // R射手爆炸
	for (int i = 1; i <= 2; i++) {
		sprintf(filename, "pictures/R-shooter-destroy-%d.png", i);
		auto image = Director::getInstance()->getTextureCache()->addImage(filename);
		auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 50, 63)));
		R_shooter_destroy.pushBack(frame);
	}
	Animation* animation3 = Animation::createWithSpriteFrames(R_shooter_destroy, 0.1f);
	AnimationCache::getInstance()->addAnimation(animation3, "R-shooter-destroy");

    // B射手爆炸
	for (int i = 1; i <= 2; i++) {
		sprintf(filename, "pictures/B-shooter-destroy-%d.png", i);
		auto image = Director::getInstance()->getTextureCache()->addImage(filename);
		auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 50, 64)));
		B_shooter_destroy.pushBack(frame);
	}
	Animation* animation4 = Animation::createWithSpriteFrames(B_shooter_destroy, 0.1f);
	AnimationCache::getInstance()->addAnimation(animation4, "B-shooter-destroy");

    // R战士爆炸
	for (int i = 1; i <= 2; i++) {
		sprintf(filename, "pictures/R-fighter-destroy-%d.png", i);
		auto image = Director::getInstance()->getTextureCache()->addImage(filename);
		auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 50, 61)));
		R_fighter_destroy.pushBack(frame);
	}
	Animation* animation5 = Animation::createWithSpriteFrames(R_fighter_destroy, 0.1f);
	AnimationCache::getInstance()->addAnimation(animation5, "R-fighter-destroy");

    // B战士爆炸
	for (int i = 1; i <= 2; i++) {
		sprintf(filename, "pictures/B-fighter-destroy-%d.png", i);
		auto image = Director::getInstance()->getTextureCache()->addImage(filename);
		auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 50, 60)));
		B_fighter_destroy.pushBack(frame);
	}
	Animation* animation6 = Animation::createWithSpriteFrames(B_fighter_destroy, 0.1f);
	AnimationCache::getInstance()->addAnimation(animation6, "B-fighter-destroy");

    // R基地爆炸
	for (int i = 1; i <= 2; i++) {
		sprintf(filename, "pictures/R-base-destroy-%d.png", i);
		auto image = Director::getInstance()->getTextureCache()->addImage(filename);
		auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 60, 57)));
		R_base_destroy.pushBack(frame);
	}
	Animation* animation7 = Animation::createWithSpriteFrames(R_base_destroy, 0.1f);
	AnimationCache::getInstance()->addAnimation(animation7, "R-base-destroy");

    // R塔爆炸动画
    for (int i = 1; i <= 3; i++) {
        sprintf(filename, "pictures/R-tower-destroy-%d.png", i);
        auto image = Director::getInstance()->getTextureCache()->addImage(filename);
        auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 150, 158)));
        R_tower_destroy.pushBack(frame);
    }
    Animation* animation7_ = Animation::createWithSpriteFrames(R_tower_destroy, 0.1f);
    AnimationCache::getInstance()->addAnimation(animation7_, "R-tower-destroy");

    // B基地爆炸动画
	for (int i = 1; i <= 2; i++) {
		sprintf(filename, "pictures/B-base-destroy-%d.png", i);
		auto image = Director::getInstance()->getTextureCache()->addImage(filename);
		auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 60, 60)));
		B_base_destroy.pushBack(frame);
	}
	Animation* animation8 = Animation::createWithSpriteFrames(B_base_destroy, 0.1f);
	AnimationCache::getInstance()->addAnimation(animation8, "B-base-destroy");

    // B塔爆炸动画
    for (int i = 1; i <= 3; i++) {
        sprintf(filename, "pictures/B-tower-destroy-%d.png", i);
        auto image = Director::getInstance()->getTextureCache()->addImage(filename);
        auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 170, 151)));
        B_tower_destroy.pushBack(frame);
    }
    Animation* animation8_ = Animation::createWithSpriteFrames(B_tower_destroy, 0.1f);
    AnimationCache::getInstance()->addAnimation(animation8_, "B-tower-destroy");
    
    // R刺客爆炸
	for (int i = 1; i <= 2; i++) {
		sprintf(filename, "pictures/R-assassin-destroy-%d.png", i);
		auto image = Director::getInstance()->getTextureCache()->addImage(filename);
		auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 50, 65)));
		R_assassin_destroy.pushBack(frame);
	}
	Animation* animation9 = Animation::createWithSpriteFrames(R_assassin_destroy, 0.1f);
	AnimationCache::getInstance()->addAnimation(animation9, "R-assassin-destroy");

    // B刺客爆炸
	for (int i = 1; i <= 2; i++) {
		sprintf(filename, "pictures/B-assassin-destroy-%d.png", i);
		auto image = Director::getInstance()->getTextureCache()->addImage(filename);
		auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 50, 65)));
		B_assassin_destroy.pushBack(frame);
	}
	Animation* animation10 = Animation::createWithSpriteFrames(B_assassin_destroy, 0.1f);
	AnimationCache::getInstance()->addAnimation(animation10, "B-assassin-destroy");

    // 红方子弹爆炸
    for (int i = 1; i <= 5; ++i) {
        sprintf(filename, "pictures/R-bullet-destroy-%d.png", i);
        auto image = Director::getInstance()->getTextureCache()->addImage(filename);
        auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 30, 30)));
        R_bullet_destroy.pushBack(frame);
    }
    Animation* animation11 = Animation::createWithSpriteFrames(R_bullet_destroy, 0.1f);
    AnimationCache::getInstance()->addAnimation(animation11, "R-bullet-destroy");
    
    // 蓝方子弹爆炸
    for (int i = 1; i <= 5; ++i) {
        sprintf(filename, "pictures/B-bullet-destroy-%d.png", i);
        auto image = Director::getInstance()->getTextureCache()->addImage(filename);
        auto frame = SpriteFrame::createWithTexture(image, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 30, 30)));
        B_bullet_destroy.pushBack(frame);
    }
    Animation* animation12 = Animation::createWithSpriteFrames(B_bullet_destroy, 0.1f);
    AnimationCache::getInstance()->addAnimation(animation12, "B-bullet-destroy");
}

void TankHonor::wallBeginMove() {
    float distance = visibleSize.height - 360.0f;
    auto moveUp = MoveBy::create(3.0f, Vec2(0, distance));
    auto moveDown = MoveBy::create(3.0f, Vec2(0, -distance));
    auto moveUpAndDown = Sequence::create(moveUp, moveDown, NULL);
    auto moveUpAndDownForever = RepeatForever::create(moveUpAndDown);
    wall->runAction(moveUpAndDownForever);
}

void TankHonor::update(float dt) {
    // 计时器
    timer++;
    if (timer == 1) {
        showHelp();
        wallBeginMove();
    }
    
    
	//检测team1和team2的坦克的状态
	for (int i = 0; i < 3; ++i) {
        // 恢复CD
        if (playerTeam1[i]->getCD() > 0) {
            playerTeam1[i]->setCD(playerTeam1[i]->getCD() - 1);
        }
        if (playerTeam2[i]->getCD() > 0) {
            playerTeam2[i]->setCD(playerTeam2[i]->getCD() - 1);
        }
		// 检测坦克的开炮状态
		if (playerTeam1[i]->getState() == TANK_STATE::ATTACKING) {
			tankFire(playerTeam1[i]);
		}
		if (playerTeam2[i]->getState() == TANK_STATE::ATTACKING) {
			tankFire(playerTeam2[i]);
		}
        if (player1Attacking) {
            if (player1->withinAttackRange(target1)) {
                player1Attacking = false;
                target1 = NULL;
            }
        }
        if (player2Attacking) {
            if (player2->withinAttackRange(target2)) {
                player2Attacking = false;
                target2 = NULL;
            }
        }
		playerTeam1[i]->avoidWall(true, wall);
		playerTeam2[i]->avoidWall(false, wall);
	}
    
    // 判断子弹是否和某个鬼东西相撞
    for (auto it = bullets.begin(); it != bullets.end();) {
        // 检测子弹是否应该消失
        if ((*it)->getTimeToDisappear() == timer) {
            (*it)->removeFromParentAndCleanup(true);
            it = bullets.erase(it);
        }
        // 检测子弹是否与可攻击的物体碰撞
        else {
            auto pos = (*it)->getPosition();
            bool hit = false;
            
            // 判断子弹是否撞墙
            if (wall->getBoundingBox().containsPoint(pos)) {
                hit = true;
                goto DELETE_BULLET;
            }
            // 判断子弹是否撞到大小龙
            else if ((*it)->testIfHit(big_dragon)) {
                if (big_dragon->getHealthValue() > 0)
                    updateHealthValueLabel(big_dragon);
                else {
                    // 大龙爆炸
                    SimpleAudioEngine::getInstance()->playEffect("sounds/boom.mp3", false);
                    string animationName = "big-dragon-destroy";
                    auto animation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
                    auto remove = CallFunc::create([&] {
                        big_dragon->setContentSize(Size(0.0f, 0.0f));
                        big_dragon->removeFromParentAndCleanup(true);
                        labels[big_dragon]->removeFromParentAndCleanup(true);
                    });
                    auto seq = Sequence::create(animation, remove, NULL);
                    big_dragon->stopAllActions();
                    big_dragon->runAction(seq);
                }
                hit = true;
                goto DELETE_BULLET;
            }
            // 判断子弹是否撞到小龙
            else if(!hit && (*it)->testIfHit(small_dragon)) {
                if (small_dragon->getHealthValue() > 0)
                    updateHealthValueLabel(small_dragon);
                else {
                    // 大龙爆炸
                    SimpleAudioEngine::getInstance()->playEffect("sounds/boom.mp3", false);
                    string animationName = "small-dragon-destroy";
                    auto animation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
                    auto remove = CallFunc::create([&] {
                        small_dragon->setContentSize(Size(0.0f, 0.0f));
                        small_dragon->removeFromParentAndCleanup(true);
                        labels[small_dragon]->removeFromParentAndCleanup(true);
                    });
                    auto seq = Sequence::create(animation, remove, NULL);
                    small_dragon->stopAllActions();
                    small_dragon->runAction(seq);
                }
                hit = true;
                goto DELETE_BULLET;
            }
            // 判断子弹是否与塔、基地、地方坦克相撞
            else if ((*it)->getTank()->getIsR()) {
                // 子弹是否与B塔相撞
                if ((*it)->testIfHit(tower2)) {
                    if (tower2->getHealthValue() > 0) {
                        target1 = tower2;
                        player1Attacking = true;
                        updateHealthValueLabel(tower2);
                    }
                    else {
                        SimpleAudioEngine::getInstance()->playEffect("sounds/boom.mp3", false);
                        string animationName = "B-tower-destroy";
                        auto animation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
                        auto remove = CallFunc::create([&] {
                            tower2->setContentSize(Size(0.0f, 0.0f));
                            tower2->removeFromParentAndCleanup(true);
                            labels[tower2]->removeFromParentAndCleanup(true);
                            SimpleAudioEngine::getInstance()->playEffect("sounds/B-comeon.mp3", false);
                        });
                        auto seq = Sequence::create(animation, remove, NULL);
                        tower2->stopAllActions();
                        tower2->runAction(seq);
                    }
                    hit = true;
                    goto DELETE_BULLET;
                }
                // 子弹是否与B基地相撞
                else if ((*it)->testIfHit(base2)) {
                    if (base2->getHealthValue() > 0) {
                        target1 = base2;
                        player1Attacking = true;
                        updateHealthValueLabel(base2);
                    }
                    else {
                        SimpleAudioEngine::getInstance()->playEffect("sounds/boom.mp3", false);
                        string animationName = "B-base-destroy";
                        auto animation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
                        auto remove = CallFunc::create([&] {
                            base2->setContentSize(Size(0.0f, 0.0f));
                            base2->removeFromParentAndCleanup(true);
                            labels[base2]->removeFromParentAndCleanup(true);
                            gameOver();
                        });
                        auto seq = Sequence::create(animation, remove, NULL);
                        base2->stopAllActions();
                        base2->runAction(seq);
                    }
                    hit = true;
                    goto DELETE_BULLET;
                }
                // 子弹是否与B方坦克相撞
                else {
                    for (auto &t: playerTeam2) {
                        if (t->getState() == TANK_STATE::DESTROYED) {
                            continue;
                        }
                        if ((*it)->testIfHit(t)) {
                            if (t->getHealthValue() > 0) {
                                target1 = t;
                                player1Attacking = true;
                                updateHealthValueLabel(t);
                            }
                            else {
                                SimpleAudioEngine::getInstance()->playEffect("sounds/boom.mp3", false);
                                string animationName;
                                if (t->getType() == TANK_TYPE::ASSASSIN)
                                    animationName = "B-assassin-destroy";
                                else if (t->getType() == TANK_TYPE::FIGHTER)
                                    animationName = "B-fighter-destroy";
                                else
                                    animationName = "B-shooter-destroy";
                                auto animation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
                                auto remove = CallFunc::create([&] {
                                    t->setContentSize(Size(0.0f, 0.0f));
                                    t->removeFromParentAndCleanup(true);
                                    labels[t]->removeFromParentAndCleanup(true);
                                });
                                auto seq = Sequence::create(animation, remove, NULL);
                                t->stopAllActions();
                                t->runAction(seq);
                                t->setState(TANK_STATE::DESTROYED);
                                if (t->getType() == player2->getType()) {
                                    changeControl(player2, playerTeam2);
                                }
                            }
                            hit = true;
                            goto DELETE_BULLET;
                        }
                    }
                }
            } else {
                // 是否正在攻击R塔
                if ((*it)->testIfHit(tower1)) {
                    if (tower1->getHealthValue() > 0) {
                        target2 = tower1;
                        player2Attacking = true;
                        updateHealthValueLabel(tower1);
                    }
                    else {
                        SimpleAudioEngine::getInstance()->playEffect("sounds/boom.mp3", false);
                        string animationName = "R-tower-destroy";
                        auto animation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
                        auto remove = CallFunc::create([&] {
                            tower1->setContentSize(Size(0.0f, 0.0f));
                            tower1->removeFromParentAndCleanup(true);
                            labels[tower1]->removeFromParentAndCleanup(true);
                            SimpleAudioEngine::getInstance()->playEffect("sounds/R-comeon.mp3", false);
                        });
                        auto seq = Sequence::create(animation, remove, NULL);
                        tower1->stopAllActions();
                        tower1->runAction(seq);
                    }
                    hit = true;
                    goto DELETE_BULLET;
                }
                // 是否在攻击R基地
                else if ((*it)->testIfHit(base1)) {
                    if (base1->getHealthValue() > 0) {
                        target2 = base1;
                        player2Attacking = true;
                        updateHealthValueLabel(base1);
                    }
                    else {
                        SimpleAudioEngine::getInstance()->playEffect("sounds/boom.mp3", false);
                        string animationName = "R-base-destroy";
                        auto animation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
                        auto remove = CallFunc::create([&] {
                            base1->setContentSize(Size(0.0f, 0.0f));
                            base1->removeFromParentAndCleanup(true);
                            labels[base1]->removeFromParentAndCleanup(true);
                        });
                        auto seq = Sequence::create(animation, remove, NULL);
                        base1->stopAllActions();
                        base1->runAction(seq);
                    }
                    hit = true;
                    goto DELETE_BULLET;
                }
                // 是否正在攻击R方坦克
                else {
                    for (auto &t: playerTeam1) {
                        if (t->getState() == TANK_STATE::DESTROYED) {
                            continue;
                        }
                        if ((*it)->testIfHit(t)) {
                            if (t->getHealthValue() > 0) {
                                target2 = t;
                                player2Attacking = true;
                                updateHealthValueLabel(t);
                            }
                            else {
                                SimpleAudioEngine::getInstance()->playEffect("sounds/boom.mp3", false);
                                string animationName;
                                if (t->getType() == TANK_TYPE::ASSASSIN)
                                    animationName = "R-assassin-destroy";
                                else if (t->getType() == TANK_TYPE::FIGHTER)
                                    animationName = "R-fighter-destroy";
                                else
                                    animationName = "R-shooter-destroy";
                                auto animation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
                                auto remove = CallFunc::create([&] {
                                    t->setContentSize(Size(0.0f, 0.0f));
                                    t->removeFromParentAndCleanup(true);
                                    labels[t]->removeFromParentAndCleanup(true);
                                });
                                auto seq = Sequence::create(animation, remove, NULL);
                                t->stopAllActions();
                                t->runAction(seq);
                                t->setState(TANK_STATE::DESTROYED);
                                if (t->getType() == player1->getType()) {
                                    changeControl(player1, playerTeam1);
                                }
                            }
                            hit = true;
                            goto DELETE_BULLET;
                        }
                    }
                }
            }
            DELETE_BULLET:
            if (hit) {
                // 子弹爆炸
                string animationName;
                if ((*it)->getTank()->getIsR()) {
                    animationName = "R-bullet-destroy";
                } else {
                    animationName = "B-bullet-destroy";
                }
                auto animation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
                auto bullet = *it;
                auto removeBullet = CallFunc::create([bullet] {
                    bullet->removeFromParentAndCleanup(true);
                });
                auto seq = Sequence::create(animation, removeBullet, NULL);
                (*it)->stopAllActions();
                (*it)->runAction(seq);
                it = bullets.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void TankHonor::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
    switch (code) {
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			isRMove = true;
			RMoveKey = 'W';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			isRMove = true;
			RMoveKey = 'S';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			isRRotate = true;
			RRotateKey = 'D';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			isRRotate = true;
			RRotateKey = 'A';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_K:
			changeControl(player1, playerTeam1);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_J:
			player1->setState(ATTACKING);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			isBMove = true;
			BMoveKey = 'W';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			isBMove = true;
			BMoveKey = 'S';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			isBRotate = true;
			BRotateKey = 'D';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			isBRotate = true;
			BRotateKey = 'A';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_2:
			changeControl(player2, playerTeam2);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_1:
			player2->setState(ATTACKING);
			break;
        default:;
    }
}

void TankHonor::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
    switch (code) {
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			RMoveKey = ' ';
			isRMove = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			RMoveKey = ' ';
			isRMove = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			RRotateKey = ' ';
			isRRotate = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			RRotateKey = ' ';
			isRRotate = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_J:
			player1->setState(NORMAL);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			BMoveKey = ' ';
			isBMove = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			BMoveKey = ' ';
			isBMove = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			BRotateKey = ' ';
			isBRotate = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			BRotateKey = ' ';
			isBRotate = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_1:
			player2->setState(NORMAL);
			break;
        default:;
    }
}

void TankHonor::gameOver() {
    auto label = Label::createWithTTF("GAME OVER!!!", "fonts/fangzhengyunu.ttf", 122.0f);
    label->setColor(Color3B::RED);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    addChild(label, 3);
	removeSchedulers();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("sounds/bgm.mp3");
	SimpleAudioEngine::getInstance()->playEffect("sounds/gameover.mp3", false);
}

void TankHonor::addSchedulers() {
    // 添加调度器
    schedule(schedule_selector(TankHonor::update), 0.1f, kRepeatForever, 0.0f);
	// 运动检测计时器
	schedule(schedule_selector(TankHonor::moveUpdate), 0.1f, kRepeatForever, 0.0f);

	schedule(schedule_selector(TankHonor::AutoTank1), 0.1f, kRepeatForever, 0);
    
    schedule(schedule_selector(TankHonor::AutoTank2), 0.1f, kRepeatForever, 0);
}

void TankHonor::AutoTank1(float dt) {
    float d;
    bool f = false;
    cocos2d::RotateTo* rotateAction = NULL;
    cocos2d::MoveTo* moveToAction = NULL;
    for (auto i : playerTeam1) {
        if (i->getState() == TANK_STATE::DESTROYED) break;
        if (i->getType() != player1->getType()) {
            if (i->getHealthValue() < 300) {
                i->lowBlood = true;
            }else i->lowBlood = false;
            
            if (i->withinAttackRange(base2)) {
                i->isAmeetBase = true;
                i->isAmeet = true;
                Point shoot = base2->getPosition() - i->getPosition();
                Point n = ccpNormalize(shoot);
                float r = atan2(n.y, -n.x);
                d = CC_RADIANS_TO_DEGREES(r);
            }
            else i->isAmeetBase = false;
            
            if (i->getPosition().getDistance(wall->getPosition()) < 50) {
                i->isAmeetWall = true;
            }
            else i->isAmeetWall = false;
            
            for (auto j : playerTeam2) {
                if (i->withinAttackRange(j)) {
                    i->isAmeet = true;
                    Point shoot = j->getPosition() - i->getPosition();
                    Point n = ccpNormalize(shoot);
                    float r = atan2(n.y, -n.x);
                    d = CC_RADIANS_TO_DEGREES(r);
                    f = false;
                }
                else f = true;
            }
            if (f == true) i->isAmeet = false;
            if (i->getPositionX() <= player1->getPositionX()) {
                if (i->lowBlood) {
                    rotateAction = RotateTo::create(0.1f, -90);
                    i->move(true, wall, labels[i], tower2);
                } else  if(player1Attacking) {
                    if(i->withinAttackRange(target1)){
                        tankFire(i);
                    }else {
                        Point shoot = target1->getPosition() - i->getPosition();
                        Point n = ccpNormalize(shoot);
                        float r = atan2(n.y, -n.x);
                        d = CC_RADIANS_TO_DEGREES(r);
                        rotateAction = RotateTo::create(0.1f, d - 90);
                        i->runAction(rotateAction);
                        i->move(true, wall, labels[i], tower2);
                    }
                }
                else {
                    if (i->isAmeetWall) {
                        rotateAction = RotateTo::create(0.1f, 180);
                        i->runAction(rotateAction);
                        i->move(true, wall, labels[i], tower2);

                    }
                    else if (i->isAmeet) {
                        rotateAction = RotateTo::create(0.1f, d - 90);
                        i->runAction(rotateAction);
                        tankFire(i);
                        //attack
                    }
                    else if (i->isAmeetBase) {
                        rotateAction = RotateTo::create(0.1f, d - 90);
                        i->runAction(rotateAction);
                        tankFire(i);
                        //attack
                    }
                    else {
                        if (i->getPositionX() > (visibleSize.width - 200)) {
                            if (i->getPositionY() >= visibleSize.height / 2) {
                                rotateAction = RotateTo::create(0.1f, 180);
                            }
                            else rotateAction = RotateTo::create(0.1f, 0);
                            i->runAction(rotateAction);
                            i->move(true, wall, labels[i], tower2);
                        }
                        else {
                            rotateAction = RotateTo::create(0.1f, 90);
                            i->runAction(rotateAction);
                            i->move(true, wall, labels[i], tower2);
                        }
                    }
                }
            }
        }
    }
}

void TankHonor::AutoTank2(float dt) {
    float d = 0;
    bool f = false;
    cocos2d::RotateTo* rotateAction = NULL;
    for (auto i : playerTeam2) {
        if (i->getState() == TANK_STATE::DESTROYED) break;
        if (i->getType() != player2->getType()) {
            if (i->getHealthValue() < 300) {
                i->lowBlood = true;
            }else i->lowBlood = false;
            
            if (i->withinAttackRange(base1)) {
                i->isAmeetBase = true;
                Point shoot = base1->getPosition() - i->getPosition();
                Point n = ccpNormalize(shoot);
                float r = atan2(n.y, -n.x);
                d = CC_RADIANS_TO_DEGREES(r);
            }
            else i->isAmeetBase = false;
            
            if (i->getPosition().getDistance(wall->getPosition()) < 50) {
                i->isAmeetWall = true;
            }
            else i->isAmeetWall = false;
            
            for (auto j : playerTeam1) {
                if (i->withinAttackRange(j)) {
                    i->isAmeet = true;
                    Point shoot = j->getPosition() - i->getPosition();
                    Point n = ccpNormalize(shoot);
                    float r = atan2(n.y, -n.x);
                    d = CC_RADIANS_TO_DEGREES(r);
                    f = false;
                }
                else f = true;
            }
            if (f == true) i->isAmeet = false;
            
            if (i->getPositionX() >= player2->getPositionX()) {
                if (i->lowBlood) {
                    rotateAction = RotateTo::create(0.1f, 90);
                    i->move(true, wall, labels[i], tower1);
                }
                else  if(player2Attacking) {
                    if(i->withinAttackRange(target2)){
                        tankFire(i);
                    }else {
                        Point shoot = target2->getPosition() - i->getPosition();
                        Point n = ccpNormalize(shoot);
                        float r = atan2(n.y, -n.x);
                        d = CC_RADIANS_TO_DEGREES(r);
                        rotateAction = RotateTo::create(0.1f, d - 90);
                        i->runAction(rotateAction);
                        i->move(true, wall, labels[i], tower1);
                    }
                }

                else {
                    if (i->isAmeetWall) {
                        rotateAction = RotateTo::create(0.1f, 180);
                        i->runAction(rotateAction);
                        i->move(true, wall, labels[i], tower1);
                    }
                    else if (i->isAmeet) {
                        rotateAction = RotateTo::create(0.1f, d - 90);
                        i->runAction(rotateAction);
                        tankFire(i);
                        //attack
                    }
                    else if (i->isAmeetBase) {
                        rotateAction = RotateTo::create(0.1f, d - 90);
                        i->runAction(rotateAction);
                        tankFire(i);
                        //attack
                    }
                    else {
                        if (i->getPositionX() < 200) {
                            if (i->getPositionY() >= visibleSize.height / 2) {
                                rotateAction = RotateTo::create(0.1f, 180);
                            }
                            else rotateAction = RotateTo::create(0.1f, 0);
                            i->runAction(rotateAction);
                            i->move(true, wall, labels[i], tower1);
                        }
                        else {
                            rotateAction = RotateTo::create(0.1f, -90);
                            i->runAction(rotateAction);
                            i->move(true, wall, labels[i], tower1);
                        }
                    }
                }
            }
        }
    }
}

void TankHonor::moveUpdate(float dt) {
	// 移动
	this->moveTank(isRMove, isRRotate, RMoveKey, RRotateKey, player1);
	this->moveTank(isBMove, isBRotate, BMoveKey, BRotateKey, player2);
}

void TankHonor::moveTank(bool isMove, bool isRotate, char moveKey, char rotateKey, Tank* player) {
    // 前后移动
	if (isMove || isRotate) {
		switch (moveKey) {
		case 'W':
                player->move(true, wall, labels[player], player->getIsR()? tower2 : tower1);
			break;
		case 'S':
            player->move(false, wall, labels[player], player->getIsR()? tower2 : tower1);
			break;
		}
		switch (rotateKey) {
		case 'A':
            player->turn(true);
			break;
		case 'D':
            player->turn(false);
			break;
		}
	}
}

void TankHonor::changeControl(Tank *&player, vector<Tank*> playerTeam) {
    for (int i = 0; i < 3; ++i) {
        if (playerTeam[i]->getType() == player->getType()) {
            if (playerTeam[(i + 1) % 3]->getState() != TANK_STATE::DESTROYED)
                player = playerTeam[(i + 1) % 3];
            else if (playerTeam[(i + 2) % 3]->getState() != TANK_STATE::DESTROYED)
                player = playerTeam[(i + 2) % 3];
            else if (player->getState() == TANK_STATE::DESTROYED) {
                gameOver();
            } else;
            break;
        }
    }
}

void TankHonor::removeSchedulers() {
	unschedule(schedule_selector(TankHonor::update));
	unschedule(schedule_selector(TankHonor::moveUpdate));
	unschedule(schedule_selector(TankHonor::AutoTank1));
	unschedule(schedule_selector(TankHonor::AutoTank2));
}

void TankHonor::tankFire(Tank* tank) {
    if (tank->getCD() == 0) {
        Bullet *bullet = Bullet::create(tank);
        bullet->setPosition(tank->getPosition());
        bullet->setRotation(tank->getRotation());
        addChild(bullet, 2);
        bullets.push_back(bullet);
        bullet->fly(timer);
        tank->setCD(10);
    }
}

void TankHonor::updateHealthValueLabel(Attackable *target) {
    float ratio = (float)target->getHealthValue() / (float)target->getHealthValueMax();
    auto label = labels[target];
    
    // 显示血条
    if      (ratio > 0.9f) label->setString("[----------]");
    else if (ratio > 0.8f) label->setString("[--------- ]");
    else if (ratio > 0.7f) label->setString("[--------  ]");
    else if (ratio > 0.6f) label->setString("[-------   ]");
    else if (ratio > 0.5f) label->setString("[------    ]");
    else if (ratio > 0.4f) label->setString("[-----     ]");
    else if (ratio > 0.3f) label->setString("[----      ]");
    else if (ratio > 0.2f) label->setString("[---       ]");
    else if (ratio > 0.1f) label->setString("[--        ]");
    else if (ratio > 0.0f) label->setString("[-         ]");
    else                   label->setString("[          ]");
    
    // 显示血条颜色
    if      (ratio > 0.67f) label->setColor(Color3B::GREEN);
    else if (ratio > 0.33f) label->setColor(Color3B::ORANGE);
    else if (ratio > 0.00f) label->setColor(Color3B::RED);
    else                    label->setColor(Color3B::BLACK);
}

Label* TankHonor::createHealthValueLabel() {
    auto label = Label::createWithTTF("[----------]", "fonts/fangzhengyunu.ttf", 10.0f);
    label->setColor(Color3B::GREEN);
    return label;
}

void TankHonor::showHelp() {
    string help1, help2;
    help1 = "Player 1:\n    WSAD to move\n    J to attack\n    K to switch tank";
    help2 = "Player 2:\n    ↑↓←→ to move\n    1 to attack\n    2 to switch tank";
    auto player1help = Label::createWithTTF(help1, "fonts/fangzhengyunu.ttf", 22.0f);
    player1help->setColor(Color3B::GRAY);
    player1help->setPosition(Vec2(100, visibleSize.height - 70));
    addChild(player1help, 1);
    auto player2help = Label::createWithTTF(help2, "fonts/fangzhengyunu.ttf", 22.0f);
    player2help->setColor(Color3B::GRAY);
    player2help->setPosition(Vec2(visibleSize.width - 10, visibleSize.height - 70));
    addChild(player2help, 1);
}
