#include "TankHonor.hpp"

Scene* TankHonor::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TankHonor::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool TankHonor::init() {
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
	addSprites();     // 添加背景和各种精灵
	addListeners();   // 添加监听器
	addSchedulers();  // 添加定时调度器
    // preloadMusic(); // 预加载音效


    // 添加调度器
    // schedule(schedule_selector(TankHonor::update), 0.01f, kRepeatForever, 0.1f);
    return true;
}

void TankHonor::addSprites() {
	// 添加地图
	auto bg = Sprite::create("pictures/map.png");
	bg->setPosition(visibleSize / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);

	// 添加坦克精灵
	player1 = new Tank();
	player1->setPosition(Vec2(50, visibleSize.height / 2));
	this->addChild(player1, 2);
}

void TankHonor::preloadMusic() {
    //auto sae = SimpleAudioEngine::getInstance();
    //
    //// 加载音效
    //sae->preloadEffect("fire.mp3");
    //sae->preloadEffect("boom.mp3");
    //sae->preloadEffect("gameover.mp3");
    //
    //// 播放背景音乐
    //sae->preloadBackgroundMusic("bgm.mp3");
    //sae->playBackgroundMusic("bgm.mp3", true);
}

void TankHonor::addListeners() {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(TankHonor::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(TankHonor::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void TankHonor::loadAnimation(string filepath) {
    /*Vector<SpriteFrame*> PlayerIdleWithBox;
    Vector<SpriteFrame*> PlayerIdleWithoutBox;
    Vector<SpriteFrame*> PlayerPutUp;
    Vector<SpriteFrame*> PlayerPutDown;
    Vector<SpriteFrame*> PlayerRunWithBox;
    Vector<SpriteFrame*> PlayerRunWithoutBox;
    Vector<SpriteFrame*> PlayerJumpWithBox;
    Vector<SpriteFrame*> PlayerJumpWithoutBox;
    
    auto PlayerImage = Director::getInstance()->getTextureCache()->addImage(filepath + ".png");
    
    PlayerIdleWithoutBox.reserve(3);
    for (int i = 0; i < 3; i++) {
        auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(32 * i, 5, 32, 36)));
        PlayerIdleWithoutBox.pushBack(frame);
    }
    Animation* PlayerIdelWithoutBoxAnimation = Animation::createWithSpriteFrames(PlayerIdleWithoutBox, 0.1f);
    AnimationCache::getInstance()->addAnimation(PlayerIdelWithoutBoxAnimation, filepath + "IdleWithoutBoxAnimation");
    
    PlayerIdleWithBox.reserve(3);
    auto IdleWithBox = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(96, 7, 32, 36)));
    PlayerIdleWithBox.pushBack(IdleWithBox);
    if (filepath == "player1")
        IdleWithBox1 = IdleWithBox;
    else IdleWithBox2 = IdleWithBox;
    for (int i = 1; i < 3; i++) {
        auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(96 + 32 * i, 7, 32, 33)));
        PlayerIdleWithBox.pushBack(frame);
    }
    Animation* PlayerIdleWithBoxAnimation = Animation::createWithSpriteFrames(PlayerIdleWithBox, 0.1f);
    AnimationCache::getInstance()->addAnimation(PlayerIdleWithBoxAnimation, filepath + "IdleWithBoxAnimation");
    
    for (int i = 0; i < 3; i++) {
        auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(96 + 32 * i, 4, 32, 36)));
        PlayerPutUp.pushBack(frame);
    }
    Animation* PlayerPutUpAnimation = Animation::createWithSpriteFrames(PlayerPutUp, 0.1f);
    AnimationCache::getInstance()->addAnimation(PlayerPutUpAnimation, filepath + "PutUpAnimation");
    
    for (int i = 0; i < 2; i++) {
        auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(193 + 32 * i, 4, 32, 36)));
        PlayerPutDown.pushBack(frame);
    }
    if (filepath == "player1")
        PlayerPutDown.pushBack(frame1);
    else
        PlayerPutDown.pushBack(frame2);
    Animation* PlayerPutDownAnimation = Animation::createWithSpriteFrames(PlayerPutDown, 0.1f);
    AnimationCache::getInstance()->addAnimation(PlayerPutDownAnimation, filepath + "PutDownAnimation");
    
    PlayerRunWithoutBox.reserve(8);
    for (int i = 0; i < 8; i++) {
        auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(32 * i, 41, 32, 36)));
        PlayerRunWithoutBox.pushBack(frame);
    }
    Animation* PlayerRunWithoutBoxAnimation = Animation::createWithSpriteFrames(PlayerRunWithoutBox, 0.1f);
    AnimationCache::getInstance()->addAnimation(PlayerRunWithoutBoxAnimation, filepath + "RunWithoutBoxAnimation");
    
    PlayerRunWithBox.reserve(8);
    for (int i = 0; i < 8; i++) {
        auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(32 * i, 81, 32, 36)));
        PlayerRunWithBox.pushBack(frame);
    }
    Animation* PlayerRunWithBoxAnimation = Animation::createWithSpriteFrames(PlayerRunWithBox, 0.1f);
    AnimationCache::getInstance()->addAnimation(PlayerRunWithBoxAnimation, filepath + "RunWithBoxAnimation");
    
    PlayerJumpWithoutBox.pushBack(SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(64, 41, 32, 36))));
    if (filepath == "player1")
        PlayerJumpWithoutBox.pushBack(frame1);
    else
        PlayerJumpWithoutBox.pushBack(frame2);
    Animation* PlayerJumpWithoutBoxAnimation = Animation::createWithSpriteFrames(PlayerJumpWithoutBox, 1.0f);
    AnimationCache::getInstance()->addAnimation(PlayerJumpWithoutBoxAnimation, filepath + "JumpWithoutBoxAnimation");
    
    PlayerJumpWithBox.pushBack(SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(64, 81, 32, 36))));
    PlayerJumpWithBox.pushBack(IdleWithBox);
    Animation* PlayerJumpWithBoxAnimation = Animation::createWithSpriteFrames(PlayerJumpWithBox, 1.0);
    AnimationCache::getInstance()->addAnimation(PlayerJumpWithBoxAnimation, filepath + "JumpWithBoxAnimation");*/
}

void TankHonor::update(float dt) {
	//移动子弹，并且判断子弹是否移出地图
	for (vector<Bullet*>::iterator i = bullets.begin(); i != bullets.end();) {
		if ((*i) != NULL) {
			(*i)->setPositionX((*i)->getPositionX() + 5 * sin((*i)->getRotation()));
			(*i)->setPositionY((*i)->getPositionY() + 5 * cos((*i)->getRotation()));
		}
		if ((*i)->getPosition().x <= 0 || (*i)->getPosition().x > visibleSize.width || (*i)->getPosition().y <= 0 || (*i)->getPosition().y > visibleSize.height) {
			(*i)->removeFromParentAndCleanup(true);
			i = bullets.erase(i);
		}
		else {
			++i;
		}
	}
}

void TankHonor::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
    switch (code) {
		case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
			isMove = true;
			moveKey = 'W';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:
			isMove = true;
			moveKey = 'S';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D:
			isRotate = true;
			rotateKey = 'D';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A:
			isRotate = true;
			rotateKey = 'A';
			break;
        //case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        //    player1->setFlippedX(true);
        //    IsPlayer1Left = true;
        //    break;
        //    
        //case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        //    player1->setFlippedX(false);
        //    IsPlayer1Right = true;
        //    break;
        //    
        //case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        //    if (!IsPlayer1Jump) {
        //        IsPlayer1Jump = true;
        //        player1->getPhysicsBody()->setVelocity(Vec2(player1->getPhysicsBody()->getVelocity().x, 200.0f));
        //    }
        //    break;

        //case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
        //case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
        //    if (!IsPlayer1Hold) {  // 如果没有举着箱子
        //        auto player1Bound = player1->getBoundingBox();
        //        for (auto b : boxes) {
        //            auto boxBound = b->getBoundingBox();
        //            if ((player1->isFlippedX()  && b->getPosition().x < player1->getPosition().x) ||
        //                (!player1->isFlippedX() && b->getPosition().x > player1->getPosition().x)) {
        //                if (player1Bound.intersectsRect(boxBound)) {
        //                    IsPlayer1Hold = true;
        //                    player1->setSpriteFrame(IdleWithBox1);
        //                    holdingBox = b;
        //                    auto newbody = PhysicsBody::createBox(b->getContentSize(), PhysicsMaterial(100.0f, 0.5f, 10.0f));
        //                    b->setPhysicsBody(newbody);
        //                    // 添加关节
        //                    joint1 = PhysicsJointDistance::construct(
        //                         player1->getPhysicsBody(), b->getPhysicsBody(), player1->getAnchorPoint(), b->getAnchorPoint());
        //                    m_world->addJoint(joint1);
        //                    break;
        //                }
        //            }
        //        }
        //    } else {  // 如果正在举着箱子
        //        IsPlayer1Hold = false;
        //        flyingBoxes.push_back(holdingBox);
        //        m_world->removeJoint(joint1);
        //        if (player1->isFlippedX()) holdingBox->getPhysicsBody()->setVelocity(Vec2(-200.0f, 300.0f));
        //        else holdingBox->getPhysicsBody()->setVelocity(Vec2(200.0f, 300.0f));
        //        player1->stopActionByTag(11);
        //        auto animation = Animate::create(AnimationCache::getInstance()->getAnimation("player1PutDownAnimation"));
        //        player1->runAction(animation);
        //    }
        //    break;
        default:;
    }
}

void TankHonor::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
    switch (code) {
		case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
			isMove = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:
			isMove = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D:
			isRotate = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A:
			isRotate = false;
			break;
        default:;
    }
}

void TankHonor::gameOver() {
    /*unschedule(schedule_selector(FriendShip::boxFall));
    unschedule(schedule_selector(FriendShip::update));
    SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm.mp3");
    SimpleAudioEngine::getInstance()->playEffect("gameover.mp3", false);
    
    auto label1 = Label::createWithTTF("单身狗，时间说没就没", "fonts/STXINWEI.TTF", 60);
    label1->setColor(Color3B(0, 0, 0));
    label1->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 100);
    this->addChild(label1);
    
    auto label2 = Label::createWithTTF("重玩", "fonts/STXINWEI.TTF", 40);
    label2->setColor(Color3B(0, 0, 0));
    auto replayBtn = MenuItemLabel::create(label2, CC_CALLBACK_1(FriendShip::replayCallback, this));
    Menu* replay = Menu::create(replayBtn, NULL);
    replay->setPosition(visibleSize.width / 2 - 200, visibleSize.height / 2);
    this->addChild(replay);
    
    auto label3 = Label::createWithTTF("退出", "fonts/STXINWEI.TTF", 40);
    label3->setColor(Color3B(0, 0, 0));
    auto exitBtn = MenuItemLabel::create(label3, CC_CALLBACK_1(FriendShip::exitCallback, this));
    Menu* exit = Menu::create(exitBtn, NULL);
    exit->setPosition(visibleSize.width / 2 + 200, visibleSize.height / 2);
    this->addChild(exit);
    
    auto submitLabel = Label::createWithTTF("提交分数", "fonts/STXINWEI.TTF", 22);
    auto submitBtn = MenuItemLabel::create(submitLabel, CC_CALLBACK_1(FriendShip::submitScore, this));
    Menu* submitMenu = Menu::create(submitBtn, NULL);
    submitMenu->setPosition(visibleSize.width / 2 - 90, visibleSize.height / 3);
    this->addChild(submitMenu);
    
    auto rankLabel = Label::createWithTTF("查看排名", "fonts/STXINWEI.TTF", 22);
    auto rankBtn = MenuItemLabel::create(rankLabel, CC_CALLBACK_1(FriendShip::seeRanking, this));
    Menu* rankMenu = Menu::create(rankBtn, NULL);
    rankMenu->setPosition(visibleSize.width / 2 + 90, visibleSize.height / 3);
    this->addChild(rankMenu);*/
}

void TankHonor::addSchedulers() {
	// 运动检测计时器
	schedule(schedule_selector(TankHonor::moveUpdate), 0.1f, kRepeatForever, 0);
}

void TankHonor::moveUpdate(float dt) {
	this->moveTank(moveKey, rotateKey, player1);
}

void TankHonor::moveTank(char moveKey, char rotateKey, Tank* player) {
	auto tank = player;
	auto nowPos = tank->getPosition();

	// 前后移动
	if (isMove) {
		switch (moveKey) {
		case 'W':
			player->runAction(
				MoveTo::create(0.1f, Vec2(
					player->getPositionX() + 5 * sin(player->getRotation()),
					player->getPositionY() + 5 * cos(player->getRotation()))));
			break;
		case 'S':
			player->runAction(
				MoveTo::create(0.1f, Vec2(
					player->getPositionX() - 5 * sin(player->getRotation()),
					player->getPositionY() - 5 * cos(player->getRotation()))));
			break;
		}
	}
	
	// 方向转动
	if (isRotate) {
		switch (rotateKey) {
		case 'D':
			player->runAction(
				RotateBy::create(0.1f, 10));
			break;
		case 'A':
			player->runAction(
				RotateBy::create(0.1f, -10));
			break;
		}
	}
}

void TankHonor::removeSchedulers() {

}

void TankHonor::replayCallback(Ref * pSender) {
    /*Director::getInstance()->replaceScene(TankHonor::createScene(::cookie));*/
}

void TankHonor::exitCallback(Ref * pSender) {
    /*Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif*/
}
