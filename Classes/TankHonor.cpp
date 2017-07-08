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
	// 红队
	Tank* RTank0 = Tank::create(true, FIGHTER);
	Tank* RTank1 = Tank::create(true, ASSASSIN);
	Tank* RTank2 = Tank::create(true, SHOOTER);
	RTank0->setPosition(Vec2(100, 100));
	RTank1->setPosition(Vec2(200, 100));
	RTank2->setPosition(Vec2(300, 100));
	RTank0->setContentSize(Size(50, 50));
	RTank1->setContentSize(Size(50, 50));
	RTank2->setContentSize(Size(50, 50));
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
	BTank0->setPosition(Vec2(visibleSize.width - 100, 100));
	BTank1->setPosition(Vec2(visibleSize.width - 200, 100));
	BTank2->setPosition(Vec2(visibleSize.width - 300, 100));
	BTank0->setContentSize(Size(50, 50));
	BTank1->setContentSize(Size(50, 50));
	BTank2->setContentSize(Size(50, 50));
	playerTeam2.push_back(BTank0);
	playerTeam2.push_back(BTank1);
	playerTeam2.push_back(BTank2);
	this->addChild(BTank0, 2);
	this->addChild(BTank1, 2);
	this->addChild(BTank2, 2);

	// 交付控制权
	player2 = BTank0;
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

	// wallMove();

	/*for (vector<Bullet*>::iterator i = bullets.begin(); i != bullets.end();) {
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
	}*/
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
			player1->setTankState(ATTACKING);
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
			player2->setTankState(ATTACKING);
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
			player1->setTankState(NORMAL);
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
			player2->setTankState(NORMAL);
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
	this->moveTank(isRMove, isRRotate, RMoveKey, RRotateKey, player1);
	this->moveTank(isBMove, isBRotate, BMoveKey, BRotateKey, player2);
}

void TankHonor::moveTank(bool isMove, bool isRotate, char moveKey, char rotateKey, Tank* player) {
	cocos2d::MoveTo* moveToAction = NULL;
	cocos2d::RotateBy* rotateAction = NULL;
	 //前后移动
	if (isMove || isRotate) {
		switch (moveKey) {
		case 'W':
			moveToAction =  MoveTo::create(0.1f, Vec2(
						player->getPositionX() + 10 * sin(CC_DEGREES_TO_RADIANS(player->getRotation())),
						player->getPositionY() + 10 * cos(CC_DEGREES_TO_RADIANS(player->getRotation()))));
			player->runAction(moveToAction);
			break;
		case 'S':
			moveToAction = MoveTo::create(0.1f, Vec2(
				player->getPositionX() - 10 * sin(CC_DEGREES_TO_RADIANS(player->getRotation())),
				player->getPositionY() - 10 * cos(CC_DEGREES_TO_RADIANS(player->getRotation()))));
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

void TankHonor::changeControl(Tank *&player, vector<Tank*> playerTeam) {
	for (auto i = 0; i < 3; i++) {
		auto value = playerTeam[i]->getType();
		auto value1 = player->getType();
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
    /*Director::getInstance()->replaceScene(TankHonor::createScene(::cookie));*/
}

void TankHonor::exitCallback(Ref * pSender) {
    /*Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif*/
}
