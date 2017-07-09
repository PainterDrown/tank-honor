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

#include <string>
using namespace CocosDenshion;

class TankHonor: public Layer {
public:
    static cocos2d::Scene* createScene();
    static TankHonor* getInstance();
    
    virtual bool init();
    CREATE_FUNC(TankHonor);
    
    void addSprites();        // 添加背景和各种精灵
    void addListeners();      // 添加监听器
    void addSchedulers();     // 添加调度器
    void removeSchedulers();  // 移除调度器
    
    void update(float dt);  // 定时更新到函数
    void moveUpdate(float dt);  // 定时更新移动函数
    void moveTank(bool isMove, bool isRotate, char moveKey, char rotateKey, Tank* player);  // 移动函数
    void changeControl(Tank *&player, vector<Tank*> playerTeam);  // 切换控制权
    void wallBeginMove();
    void addBullet(Bullet *bullet);
    
    // 键盘事件回调函数
    void onKeyPressed(EventKeyboard::KeyCode code, Event * event);
    void onKeyReleased(EventKeyboard::KeyCode code, Event * event);
    
    void preloadMusic();                  // 预加载音乐
    void gameOver();                      // 游戏结束
    void loadAnimation(string filepath);  // 加载动画
    
    void replayCallback(Ref *pSender);  // 重玩按钮响应函数
    void exitCallback(Ref *pSender);    // 退出按钮响应函数
private:
    static TankHonor *layer;
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
	vector<Bullet*> bullets;
	Tank *player1, *player2;
	Wall *wall;
	Base *base1, *base2;
    Tower *tower1, *tower2;
    
    // 大龙和小龙
    Dragon *big_dragon, *small_dragon;
    
    // 显示信息
    Label *label;
    int timer;  // 计时器，以秒为单位
};
#endif
