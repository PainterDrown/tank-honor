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
	Tank* AITank0 = Tank::create(true, FIGHTER);
	Tank* AITank1 = Tank::create(true, ASSASSIN);
	Tank* AITank2 = Tank::create(true, SHOOTER);
	AITank0->setPosition(Vec2(50, visibleSize.height / 2));
	AITank1->setPosition(Vec2(50, visibleSize.height / 3));
	AITank2->setPosition(Vec2(50, 2 * visibleSize.height / 3));
	AITank0->setContentSize(Size(50, 50));
	AITank1->setContentSize(Size(50, 50));
	AITank2->setContentSize(Size(50, 50));
	playerTeam1.push_back(AITank0);
	playerTeam1.push_back(AITank1);
	playerTeam1.push_back(AITank2);
	this->addChild(AITank0, 2);
	this->addChild(AITank1, 2);
	this->addChild(AITank2, 2);

	// 交付控制权
	player1 = AITank0;
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

void TankHonor::wallMove() {
	MoveTo* moveToAction;
	if (wall->getPosition().y < 0) {
		wall->stopAllActions();
		moveToAction = MoveTo::create(0.1f, Vec2(wall->getPosition().x, visibleSize.height + 100));
		wall->runAction(moveToAction);
	}
	else if (wall->getPosition().y > visibleSize.height) {
		wall->stopAllActions();
		moveToAction = MoveTo::create(0.1f, Vec2(wall->getPosition().x, -100));
		wall->runAction(moveToAction);
	}
}

void TankHonor::update(float dt) {
	//1.判断子弹是否发射，若没有发射，调用fly函数
	//2.判断子弹是否出界
	//3.判断子弹是否撞到墙壁或是坦克
	//4.移动子弹，并且判断子弹是否移出地图
	//5.移动墙壁

	wallMove();

	for (vector<Bullet*>::iterator i = bullets.begin(); i != bullets.end();) {
		bool tempState = false;
		if ((*i)->getState() == WAITING) {
			(*i)->fly();
		}
		if ((*i)->getPosition().x <= 0 || (*i)->getPosition().x > visibleSize.width || (*i)->getPosition().y <= 0 || (*i)->getPosition().y > visibleSize.height) {
			(*i)->removeFromParentAndCleanup(true);
			i = bullets.erase(i);
			tempState = true;
		}
		else if (wall->getPosition().getDistance((*i)->getPosition()) < 30) {
			(*i)->destroy();
			(*i)->removeFromParentAndCleanup(true);
			i = bullets.erase(i);
			tempState = true;
		}
		for (int j = 0; j < 3; j++) {
			playerTeam1[j]->AI();
			playerTeam2[j]->AI();
			int dis1 = playerTeam1[j]->getPosition().getDistance((*i)->getPosition());
			int dis2 = playerTeam2[j]->getPosition().getDistance((*i)->getPosition());
			if (dis1 < 30 || dis2 < 30) {
				(*i)->hit();
				(*i)->removeFromParentAndCleanup(true);
				i = bullets.erase(i);
				tempState = true;
				if (dis1 < 30) { playerTeam1[j]->hurt(); }
				else if (dis2 < 30) { playerTeam2[j]->hurt(); }
			}
		}
		if (tempState == false) {
			++i;
		}
	}
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
		case cocos2d::EventKeyboard::KeyCode::KEY_K:
			changeControl();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_J:
			player1->setTankState(ATTACKING);
			break;
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
		case cocos2d::EventKeyboard::KeyCode::KEY_J:
			player1->setTankState(NORMAL);
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
	// 移动
	this->moveTank(moveKey, rotateKey, player1);
}

void TankHonor::moveTank(char moveKey, char rotateKey, Tank* player) {
	auto tank = player;
	auto nowPos = tank->getPosition();
	cocos2d::MoveTo* moveToAction = NULL;
	cocos2d::RotateBy* rotateAction = NULL;
	 //前后移动
	if (isMove || isRotate) {
		switch (moveKey) {
		case 'W':
			moveToAction =  MoveTo::create(0.1f, Vec2(
						player->getPositionX() + 10 * sin(CC_DEGREES_TO_RADIANS(player->getRotation()) + CC_DEGREES_TO_RADIANS(90)),
						player->getPositionY() + 10 * cos(CC_DEGREES_TO_RADIANS(player->getRotation()) + CC_DEGREES_TO_RADIANS(90))));
			player->runAction(moveToAction);
			break;
		case 'S':
			moveToAction = MoveTo::create(0.1f, Vec2(
				player->getPositionX() - 10 * sin(CC_DEGREES_TO_RADIANS(player->getRotation()) + CC_DEGREES_TO_RADIANS(90)),
				player->getPositionY() - 10 * cos(CC_DEGREES_TO_RADIANS(player->getRotation()) + CC_DEGREES_TO_RADIANS(90))));
			player->runAction(moveToAction);
			break;
		}
		switch (rotateKey) {
		case 'A':
			rotateAction = RotateBy::create(0.1f, (-10));
			player->runAction(rotateAction);
			break;
		case 'D':
			rotateAction = RotateBy::create(0.1f, (10));
			player->runAction(rotateAction);
			break;
		}
	}
}

void TankHonor::changeControl() {
	for (auto i = 0; i < 3; i++) {
		auto value = playerTeam1[i]->getType();
		auto value1 = player1->getType();
		if (playerTeam1[i]->getType() == player1->getType()) {
			if (i == 2) {
				player1 = playerTeam1[0];
			}
			else {
				player1 = playerTeam1[i + 1];
			}
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
