#ifndef TANK_HONOR
#define TANK_HONOR

#pragma execution_character_set("utf-8")

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "models/Tank.hpp"
#include "models/Bullet.hpp"
#include "models/Wall.hpp"
#include "models/Base.hpp"
#include "models/Tower.hpp"
#include "models/Dragon.hpp"
USING_NS_CC;
using namespace CocosDenshion;

#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;


class TankHonor: public Layer {
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    CREATE_FUNC(TankHonor);
    
    void addSprites();        // 添加背景和各种精灵
    void addListeners();      // 添加监听器
    void addSchedulers();     // 添加调度器
    void removeSchedulers();  // 移除调度器
    
    void update(float dt);  // 定时更新到函数
	void AutoTank1(float dt); //fake AI
    void AutoTank2(float dt); //fake AI
    void moveUpdate(float dt);  // 定时更新移动函数
    void moveTank(bool isMove, bool isRotate, char moveKey, char rotateKey, Tank* player);  // 移动函数
    void changeControl(Tank *&player, vector<Tank*> playerTeam);  // 切换控制权
    void wallBeginMove();
    void tankFire(Tank* tank);
    void updateHealthValueLabel(Attackable *target);
    Label* createHealthValueLabel();
    void gameOver();                      // 游戏结束
    void showHelp();
    
    // 键盘事件回调函数
    void onKeyPressed(EventKeyboard::KeyCode code, Event * event);
    void onKeyReleased(EventKeyboard::KeyCode code, Event * event);
    
    void preloadMusic();                  // 预加载音乐
    void loadAnimation();  // 加载动画

private:
    Size visibleSize;
    
    // SpriteFrame *frame1;
    // SpriteFrame *frame2;
    
	// 辅助信息
	bool isRMove;    // 判断是否运动
	bool isRRotate;  // 判断是否旋转
	char RMoveKey;   // 按键判断
	char RRotateKey; // 旋转按键判断
	bool isBMove;    // 判断是否运动
	bool isBRotate;  // 判断是否旋转
	char BMoveKey;   // 按键判断
	char BRotateKey; // 旋转按键判断

	//玩家队伍和子弹
	vector<Tank*> playerTeam1;
	vector<Tank*> playerTeam2;
	list<Bullet*> bullets;
	Tank *player1, *player2;
	Wall *wall;
	Base *base1, *base2;
    Tower *tower1, *tower2;
    Attackable *target1, *target2;
    bool player1Attacking, player2Attacking;
    
    // 大龙和小龙
    Dragon *big_dragon, *small_dragon;
    
    // 计时器，以100ms为单位
    int timer;
    
    // 血条
    map<Attackable*, Label*> labels;
//    Label *RTank0_label,
//          *RTank1_label,
//          *RTank2_label,
//          *BTank0_label,
//          *BTank1_label,
//          *BTank2_label,
//          *RTower_label,
//          *BTower_label,
//          *RBase_label,
//          *BBase_label,
//          *big_dragon_label,
//          *small_dragon_label;
};
#endif
