#include "TankHonor.hpp"

class Bullet;
class Tank;

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
    label = Label::createWithTTF("Rotation: ", "fonts/fangzhengyunu.ttf", 22.0f);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    addChild(label, 3);
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

void TankHonor::loadAnimation(string filepath) {
    
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
    static int count = 0;
    if (count == 0) {
        wallBeginMove();
    }
    if (count % 10 == 0) {
        timer++;
    }
    
    // 1.判断子弹是否发射，若没有发射，调用fly函数
    // 2.判断子弹是否出界
    // 3.判断子弹是否撞到墙壁或是坦克
    // 4.移动子弹，并且判断子弹是否移出地图
    // 5.移动墙壁
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
	//		//if (playerTeam1[j]->getType() == player1->getType()) { playerTeam1[j]->AI(); }
	//		//if (playerTeam2[j]->getType() == player2->getType()) { playerTeam2[j]->AI(); }
	//		int dis1 = playerTeam1[j]->getPosition().getDistance((*i)->getPosition());
	//		int dis2 = playerTeam2[j]->getPosition().getDistance((*i)->getPosition());
	//		if (dis1 < 30 || dis2 < 30) {
	//			(*i)->removeFromParentAndCleanup(true);
	//			tempState = true;
	//			if (dis1 < 30) {
 //                   (*i)->hit(playerTeam1[j]);
 //               }
	//			else if (dis2 < 30) {
 //                   (*i)->hit(playerTeam2[j]);
 //               }
 //               i = bullets.erase(i);
	//		}
	//	}
	//	if (tempState == false) {
	//		++i;
	//	}
	//}
 //   
    count++;
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
    schedule(schedule_selector(TankHonor::update), 0.1f, kRepeatForever, 0.1f);
	// 运动检测计时器
	schedule(schedule_selector(TankHonor::moveUpdate), 0.1f, kRepeatForever, 0);
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
            player->move(true);
			break;
		case 'S':
            player->move(false);
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
    /*Director::getInstance()->replaceScene(TankHonor::createScene(::cookie));*/
}

void TankHonor::exitCallback(Ref * pSender) {
    /*Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif*/
}

void TankHonor::addBullet(Bullet *bullet) {
    bullets.push_back(bullet);
}
