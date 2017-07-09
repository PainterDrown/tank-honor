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
    
    preloadMusic();  // 预加载音效
    
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
	RTank0->setPosition(Vec2(200.0f, visibleSize.height / 2 + 100.0f));
	RTank1->setPosition(Vec2(200.0f, visibleSize.height / 2));
	RTank2->setPosition(Vec2(200.0f, visibleSize.height / 2 - 100.0f));
	RTank0->setContentSize(Size(70, 70));
	RTank1->setContentSize(Size(70, 70));
	RTank2->setContentSize(Size(70, 70));
	playerTeam1.push_back(RTank0);
	playerTeam1.push_back(RTank1);
	playerTeam1.push_back(RTank2);
	this->addChild(RTank0, 2);
	this->addChild(RTank1, 2);
	this->addChild(RTank2, 2);

	// 交付控制权
	player1 = RTank0;

	// 蓝队
	Tank* BTank0 = Tank::create(false, FIGHTER);
	Tank* BTank1 = Tank::create(false, ASSASSIN);
	Tank* BTank2 = Tank::create(false, SHOOTER);
	BTank0->setPosition(Vec2(visibleSize.width - 200.0f, visibleSize.height / 2 + 100.0f));
	BTank1->setPosition(Vec2(visibleSize.width - 200.0f, visibleSize.height / 2));
	BTank2->setPosition(Vec2(visibleSize.width - 200.0f, visibleSize.height / 2 - 100.0f));
	BTank0->setContentSize(Size(70, 70));
	BTank1->setContentSize(Size(70, 70));
	BTank2->setContentSize(Size(70, 70));
	playerTeam2.push_back(BTank0);
	playerTeam2.push_back(BTank1);
	playerTeam2.push_back(BTank2);
	this->addChild(BTank0, 2);
	this->addChild(BTank1, 2);
	this->addChild(BTank2, 2);

	// 交付控制权
	player2 = BTank0;
    
    // R基地
    tower1 = Tower::create(true);
    tower1->setPosition(Vec2(70, visibleSize.height / 2));
    tower1->setContentSize(Size(180, 180));
    addChild(tower1, 2);
    base1 = Base::create(true);
    base1->setPosition(Vec2(50, visibleSize.height / 2));
    base1->setContentSize(Size(80, 80));
    addChild(base1, 2);
    
    // B基地
    tower2 = Tower::create(false);
    tower2->setPosition(Vec2(visibleSize.width - 70.0f, visibleSize.height / 2));
    tower2->setContentSize(Size(180, 180));
    addChild(tower2, 2);
    base2 = Base::create(false);
    base2->setPosition(Vec2(visibleSize.width - 50.0f, visibleSize.height / 2));
    base2->setContentSize(Size(80, 80));
    addChild(base2, 2);

	// 墙实例
	wall = Wall::create();
	wall->setPosition(Vec2(visibleSize.width / 2, 180.0f));
    wall->setContentSize(Size(40, 140));
	this->addChild(wall);
    
    // 大龙和小龙
    big_dragon = Dragon::create(true);
    big_dragon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 60.0f));
    big_dragon->setContentSize(Size(100.0f, 100.0f));
    addChild(big_dragon);
    small_dragon = Dragon::create(false);
    small_dragon->setPosition(Vec2(visibleSize.width / 2, 60.0f));
    small_dragon->setContentSize(Size(100.0f, 100.0f));
    addChild(small_dragon);
    
    // 添加信息标签
    // label = Label::createWithTTF("Rotation: ", "fonts/fangzhengyunu.ttf", 22.0f);
    // label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    // addChild(label, 3);
}

void TankHonor::preloadMusic() {
    auto sae = SimpleAudioEngine::getInstance();
    
    //// 加载音效
    //sae->preloadEffect("fire.mp3");
    //sae->preloadEffect("boom.mp3");
    //sae->preloadEffect("gameover.mp3");
    
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
        wallBeginMove();
    }
    
    // 开炮
    for (int i = 0; i < 3; ++i) {
        if (playerTeam1[i]->getState() == TANK_STATE::ATTACKING) {
            tankFire(playerTeam1[i]);
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (playerTeam2[i]->getState() == TANK_STATE::ATTACKING) {
            tankFire(playerTeam2[i]);
        }
    }
    
    for (auto it = bullets.begin(); it != bullets.end(); ++it) {
        // 检测子弹是否应该消失
        if ((*it)->getTimeToDisappear() == timer) {
            (*it)->removeFromParentAndCleanup(true);
            it = bullets.erase(it);
        } else {
            auto pos = (*it)->getPosition();
            bool hit = false;
            // 判断子弹是否撞墙
            if (wall->getBoundingBox().containsPoint(pos)) {
                hit = true;
            }
            // 判断子弹是否撞到大小龙
            if ((*it)->testIfHit(big_dragon));
            else (*it)->testIfHit(small_dragon);
            
            // 判断子弹是否与塔、基地、地方坦克相撞
            if ((*it)->getTank()->getIsR()) {
                if (tower2 && (*it)->testIfHit(tower2));
                else if ((*it)->testIfHit(base2));
                else {
                    for (auto t: playerTeam2) {
                        if ((*it)->testIfHit(t)) {
                            break;
                        }
                    }
                }
            } else {
                if (tower1 && (*it)->testIfHit(tower1));
                else if ((*it)->testIfHit(base1));
                else {
                    for (auto t: playerTeam1) {
                        if ((*it)->testIfHit(t)) {
                            break;
                        }
                    }
                }
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
}

void TankHonor::addSchedulers() {
    // 添加调度器
    schedule(schedule_selector(TankHonor::update), 0.1f, kRepeatForever, 0.0f);
	// 运动检测计时器
	schedule(schedule_selector(TankHonor::moveUpdate), 0.1f, kRepeatForever, 0.0f);

	schedule(schedule_selector(TankHonor::AutoTank), 0.1f, kRepeatForever, 0);
}

void TankHonor::AutoTank(float dt) {
	bool f = false;
	cocos2d::RotateTo* rotateAction = NULL;
	cocos2d::MoveTo* moveToAction = NULL;
	for (auto i : playerTeam1) {
		if (i->getType() != player1->getType()) {
			if (i->getHealthValue() < 300) {
				i->lowBlood = true;
			}else i->lowBlood = false;

			if (i->getPosition().getDistance(wall->getPosition()) < (i->getAttackRange() / 10)) {
				i->isAmeetWall = true;
			}
			else i->isAmeetWall = false;

			for (auto j : playerTeam2) {
				if (i->getPosition().getDistance(j->getPosition()) < (i->getAttackRange() / 10)) {
					i->isAmeet = true;
					f = false;
				}
				else f = true;
			}
			if (f == true) i->isAmeet = false;



			if (i->lowBlood) {
				rotateAction = RotateTo::create(0.1f, -90);
				moveToAction = MoveTo::create(0.3f, Vec2(
					i->getPositionX() + 30 * sin(CC_DEGREES_TO_RADIANS(i->getRotation())),
					i->getPositionY() + 30 * cos(CC_DEGREES_TO_RADIANS(i->getRotation()))));
				i->runAction(moveToAction);
			}
			else {
				if (i->isAmeetWall) {
					rotateAction = RotateTo::create(0.1f, 180);
					i->runAction(rotateAction);
					moveToAction = MoveTo::create(0.5f, Vec2(
						i->getPositionX() + 30 * sin(CC_DEGREES_TO_RADIANS(i->getRotation())),
						i->getPositionY() + 30 * cos(CC_DEGREES_TO_RADIANS(i->getRotation()))));
					i->runAction(moveToAction);
				}
				else if (i->isAmeet) {

				}
				else {
					rotateAction = RotateTo::create(0.1f, 90);
					i->runAction(rotateAction);
					moveToAction = MoveTo::create(0.3f, Vec2(
						i->getPositionX() + 30 * sin(CC_DEGREES_TO_RADIANS(i->getRotation())),
						i->getPositionY() + 30 * cos(CC_DEGREES_TO_RADIANS(i->getRotation()))));
					i->runAction(moveToAction);
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
            player->move(true, wall);
			break;
		case 'S':
            player->move(false, wall);
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
	for (auto i = 0; i < 3; i++) {
		if (playerTeam[i]->getType() == player->getType()) {
			if (i == 2) {
				player = playerTeam[0];
			}
			else {
				player = playerTeam[i + 1];
			}
			break;
		}
	}
}

void TankHonor::removeSchedulers() {

}

void TankHonor::replayCallback(Ref * pSender) {
    
}

void TankHonor::exitCallback(Ref * pSender) {
    /*Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif*/
}

void TankHonor::tankFire(Tank* tank) {
    Bullet *bullet = Bullet::create(tank);
    
    bullet->setPosition(tank->getPosition());
    bullet->setContentSize(Size(20, 20));
    bullet->setRotation(tank->getRotation());
    addChild(bullet, 2);
    bullets.push_back(bullet);
    bullet->fly(timer);
}
