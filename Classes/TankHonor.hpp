#ifndef TANK_HONOR
#define TANK_HONOR

#pragma execution_character_set("utf-8")

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

class TankHonor : public Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TankHonor);  // implement the "static create()" method manually
    
    void addSprites();        // 添加背景和各种精灵
    void addListeners();      // 添加监听器
    void addSchedulers();     // 添加调度器
    void removeSchedulers();  // 移除调度器
    
    void update(float dt);  // 定时更新到函数
    
    // 键盘事件回调函数
    void onKeyPressed(EventKeyboard::KeyCode code, Event * event);
    void onKeyReleased(EventKeyboard::KeyCode code, Event * event);
    
    void preloadMusic();                  // 预加载音乐
    void GameOver();                      // 游戏结束
    void loadAnimation(string filepath);  // 加载动画
    
    void replayCallback(Ref * pSender);  // 重玩按钮响应函数
    void exitCallback(Ref * pSender);    // 退出按钮响应函数
    
private:
    Size visibleSize;
    
    SpriteFrame* frame1;
    SpriteFrame* frame2;

	//玩家队伍和子弹
	vector<Tank*> playerTeam1;
	vector<Tank*> playerTeam2;
	vector<Bullets*> bullets;
	Tank * player1, player2;

    // 显示信息
    Label *timeLabel, *scoreLabel, *info;
};

class Tank : public Sprite {
public:
    Tank(const int type);
    void attack(Tank &other);

private:
    int type;
    int health_value;    // 生命值
    int attack_value;    // 攻击力
    int defense_value;   // 防御力
    int attack_range;    // 射程
};



#endif
