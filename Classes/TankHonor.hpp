#ifndef TANK_HONOR
#define TANK_HONOR

#pragma execution_character_set("utf-8")

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

enum TANK_STATE {
    NORMAL,     // 正常状态，不用进行特殊处理
    ATTACKING,  // 正要发动攻击，检测到时要播放进攻动画
    DESTROYED   // 生命值为0时触发这个状态，播放爆炸动画
};

enum TANK_TYPE {
    ASSASSIN,  // 刺客：血量中，伤害力高，防御力中，射程短，速度高，子弹速度中
    FIGHTER,   // 战士：血量高，伤害力中，防御力高，射程中，速度中，子弹速度低
    SHOOTER    // 射手：血量低，伤害力低，防御力低，射程长，速度低，子弹速度高
};

enum BULLET_STATE {
    WAITING,
    FLYING
};

class Tank: public Sprite {
public:
    // 默认是战士型坦克
    Tank() {
        this->type = TANK_TYPE::FIGHTER;
    }
    
    // 设置坦克的类型
    Tank(const TANK_TYPE type) {
        this->type = type;
    }
    
    void initAttributes() {
        switch(type) {
            case TANK_TYPE::ASSASSIN:
                health_value = 800;
                attack_value = 200;
                defense_value = 150;
                attack_range = 1000;  // 1000ms
                speed = 
                break;
            case TANK_TYPE::FIGHTER:
                break;
            case TANK_TYPE::SHOOTER:
                break;
        }
    }
    
    int getAttackValue() const {
        return attack_range;
    }
    
    
    
private:
    // 坦克的类型
    TANK_TYPE type;
    
    int health_value;    // 生命值
    int attack_value;    // 攻击力
    int defense_value;   // 防御力
    int attack_range;    // 射程
    int speed;           // 速度
    int bullet_speed;    // 子弹速度
    
    // 当前的方向，x轴方向为0度，逆时针方向为正
    // 一开始R方的坦克为0度，B方的坦克为180度
    int direction;
};

class Bullet: public Sprite {
public:
    static Bullet* create(const TANK_TYPE type,
                          const int attack_value,
                          const int attack_range,
                          const int bullet_speed) {
        // 申请内存空间
        Bullet *bullet = new Bullet();
        
        // 绑定图片
        switch(type) {
            case TANK_TYPE::ASSASSIN:
                bullet->initWithFile("bullet-assassin");
                break;
            case TANK_TYPE::FIGHTER:
                bullet->initWithFile("bullet-fighter");
                break;
            case TANK_TYPE::SHOOTER:
                bullet->initWithFile("bullet-shooter");
                break;
            default:
                if (bullet) {
                    delete bullet;
                }
                return NULL;
        }
        
        // 绑定属性
        bullet->type = type;
        bullet->attack_value = attack_value;
        bullet->attack_range = attack_range;
        bullet->bullet_speed = bullet_speed;
        
        return bullet;
    }
    
    int calculateDamage(const Tank &tank) {
        static const int BASE = 1024;
        return attack_value * (1 - (double)tank.getAttackValue() / BASE);
    }
    
    BULLET_STATE getState() const {
        return state;
    }
private:
    TANK_TYPE type;
    BULLET_STATE state;
    int attack_value;
    int attack_range;
    int bullet_speed;
};

class TankHonor: public Layer {
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
    void gameOver();                      // 游戏结束
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
	vector<Bullet*> bullets;
	Tank * player1, player2;

    // 显示信息
    Label *timeLabel, *scoreLabel, *info;
};



#endif
