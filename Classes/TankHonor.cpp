#include "TankHonor.hpp"

TankHonor *TankHonor::layer = NULL;

Scene* TankHonor::createScene() {
    auto scene = Scene::create();
    layer = TankHonor::create();
    scene->addChild(layer);
    return scene;
}

TankHonor* TankHonor::getInstance() {
    return layer;
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

    schedule(schedule_selector(TankHonor::update), 0.1f, kRepeatForever, 0.1f);
    
    return true;
}

void TankHonor::addSprites() {
	// 添加地图
	auto bg = Sprite::create("pictures/map.png");
	bg->setPosition(visibleSize / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);

	// 添加坦克精灵
	player1 = Tank::create();
	player1->setPosition(Vec2(50, visibleSize.height / 2));
	//player1->setAnchorPoint(Vec2(player1->getContentSize().width, player1->getContentSize().height / 2));
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
    
}

void TankHonor::update(float dt) {
	////1.判断子弹是否发射，若没有发射，调用fly函数
	////2.判断子弹是否出界
	////3.判断子弹是否撞到墙壁或是坦克
	////移动子弹，并且判断子弹是否移出地图
	//for (vector<Bullet*>::iterator i = bullets.begin(); i != bullets.end();) {
	//	bool tempState = false;
	//	if ((*i)->getState() == WAITING) {
	//		(*i)->fly();
	//	}
	//	if ((*i)->getPosition().x <= 0 || (*i)->getPosition().x > visibleSize.width || (*i)->getPosition().y <= 0 || (*i)->getPosition().y > visibleSize.height) {
	//		(*i)->removeFromParentAndCleanup(true);
	//		i = bullets.erase(i);
	//		tempState = true;
	//	}
	//	else if (wall->getPosition().getDistance((*i)->getPosition()) < 30) {
	//		(*i)->destroy();
	//		(*i)->removeFromParentAndCleanup(true);
	//		i = bullets.erase(i);
	//		tempState = true;
	//	}
	//	for (int j = 0; j < 3; j++) {
	//		playerTeam1[j]->AI();
	//		playerTeam2[j]->AI();
	//		int dis1 = playerTeam1[j]->getPosition().getDistance((*i)->getPosition());
	//		int dis2 = playerTeam2[j]->getPosition().getDistance((*i)->getPosition());
	//		if (dis1 < 30 || dis2 < 30) {
	//			(*i)->hit();
	//			(*i)->removeFromParentAndCleanup(true);
	//			i = bullets.erase(i);
	//			tempState = true;
	//			if (dis1 < 30) { playerTeam1[j]->hurt(); }
	//			else if (dis2 < 30) { playerTeam2[j]->hurt(); }
	//		}
	//	}
	//	if (tempState == false) {
	//		++i;
	//	}
	//}
}

void TankHonor::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
    switch (code) {
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			isMove = true;
			moveKey = 'W';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			isMove = true;
			moveKey = 'S';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			isRotate = true;
			rotateKey = 'D';
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
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
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			moveKey = ' ';
			isMove = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			moveKey = ' ';
			isMove = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			rotateKey = ' ';
			isRotate = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			rotateKey = ' ';
			isRotate = false;
			break;
        default:;
    }
}

void TankHonor::gameOver() {
    
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
	cocos2d::MoveTo* moveToAction = NULL;
	cocos2d::RotateBy* rotateAction = NULL;
	 //前后移动
	if (isMove || isRotate) {
		//switch (moveKey) {
		//case 'W':
		//	moveToAction = MoveTo::create(0.1f, Vec2(
		//		player->getPositionX() + 10 * sin(player->getRotation() + CC_DEGREES_TO_RADIANS(90)),
		//		player->getPositionY() + 10 * cos(player->getRotation() + CC_DEGREES_TO_RADIANS(90))));
		//	rotateAction = RotateBy::create(0.1f, 0);
		//	if (isRotate) {
		//		switch (rotateKey) {
		//		case 'D':
		//			/*moveToAction = MoveTo::create(0.1f, Vec2(
		//				player1->getPositionX() + 
		//			))
		//			rotateAction = RotateBy::create(0.1f, 5);*/
		//			break;
		//		case 'A':
		//			rotateAction = RotateBy::create(0.1f, -5);
		//			break;
		//		}
		//	}
		//	player->runAction(Sequence::create(rotateAction, moveToAction, NULL));
		//	break;
		//case 'S':
		//	moveToAction = MoveTo::create(0.1f, Vec2(
		//		player->getPositionX() - 10 * sin(player->getRotation() + CC_DEGREES_TO_RADIANS(90)),
		//		player->getPositionY() - 10 * cos(player->getRotation() + CC_DEGREES_TO_RADIANS(90))));
		//	rotateAction = RotateBy::create(0.1f, 0);
		//	if (isRotate) {
		//		switch (rotateKey) {
		//		case 'D':
		//			rotateAction = RotateBy::create(0.1f, 10);
		//			moveToAction = MoveTo::create(0.1f, Vec2(
		//				player->getPositionX() - 10 * sin(player->getRotation() + CC_DEGREES_TO_RADIANS(100)),
		//				player->getPositionY() - 10 * cos(player->getRotation() + CC_DEGREES_TO_RADIANS(100))));
		//			break;
		//		case 'A':
		//			rotateAction = RotateBy::create(0.1f, -10);
		//			moveToAction = MoveTo::create(0.1f, Vec2(
		//				player->getPositionX() - 10 * sin(player->getRotation() + CC_DEGREES_TO_RADIANS(80)),
		//				player->getPositionY() - 10 * cos(player->getRotation() + CC_DEGREES_TO_RADIANS(80))));
		//			break;
		//		}
		//	}
		//	player->runAction(Sequence::create(Spawn::create(rotateAction, moveToAction), nullptr));

		//	break;
		//}
		switch (moveKey)
		{
		case 'W':
			moveToAction =  MoveTo::create(0.1f, Vec2(
						player->getPositionX() + 10 * sin(player->getRotation() + CC_DEGREES_TO_RADIANS(90)),
						player->getPositionY() + 10 * cos(player->getRotation() + CC_DEGREES_TO_RADIANS(90))));
			player->runAction(moveToAction);
			break;
		case 'S':
			moveToAction = MoveTo::create(0.1f, Vec2(
				player->getPositionX() - 10 * sin(player->getRotation() + CC_DEGREES_TO_RADIANS(90)),
				player->getPositionY() - 10 * cos(player->getRotation() + CC_DEGREES_TO_RADIANS(90))));
			player->runAction(moveToAction);
			break;
		}
		switch (rotateKey)
		{
			float value;
			float value2;
		case 'A':
			value = CC_RADIANS_TO_DEGREES(player->getRotation());
			value2 = player->getRotation();
			rotateAction = RotateBy::create(0.1f, CC_DEGREES_TO_RADIANS(-10));
			player->runAction(rotateAction);
			value = CC_RADIANS_TO_DEGREES(player->getRotation());
			value2 = player->getRotation();
			break;
		case 'D':
			rotateAction = RotateBy::create(0.1f, CC_DEGREES_TO_RADIANS(10));
			player->runAction(rotateAction);
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
