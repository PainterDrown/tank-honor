#ifndef BULLET
#define BULLET

#include "cocos2d.h"
#include "enums.hpp"
#include "Tank.hpp"
#include <string>
USING_NS_CC;
using namespace std;

class Tank;

class Bullet: public Sprite {
public:
    static Bullet* create(const TANK_TYPE type,
                          const int attack_value,
                          const int attack_range,
                          const int bullet_speed);
    
    // 计算子弹打中某只坦克后造成的伤害
    int calculateDamage(const Tank *tank) const;
    
    // 获取当前子弹的状态
    BULLET_STATE getState() const;
    
    // 让子弹飞
    void fly();
    
    // 播放子弹爆炸动画
    void destroy();
    
    // 子弹撞到坦克，播放爆炸的同时坦克收到伤害
    void hit(const Tank *tank);
    
private:
    TANK_TYPE type;
    BULLET_STATE state;
    bool control;
    int attack_value;
    int attack_range;
    int bullet_speed;
};


#endif
