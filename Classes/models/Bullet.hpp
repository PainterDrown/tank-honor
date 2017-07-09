#ifndef BULLET
#define BULLET

#include "cocos2d.h"
#include "enums.hpp"
#include "Attackable.hpp"
#include "Tank.hpp"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

#include <string>
using namespace std;

class Tank;

class Bullet: public Sprite {
public:
    static Bullet* create(Tank *tank);
    
    // 计算子弹打中某只坦克后造成的伤害
    int calculateDamage(const Attackable *target) const;
    
    // 子弹撞到坦克，播放爆炸的同时坦克收到伤害
    void testIfHit(Attackable *target);
    
    // 获取当前子弹的状态
    BULLET_STATE getState() const;
    
    // 让子弹飞
    void fly(const int timer);
    
    // 播放子弹爆炸动画
    void destroy();
    
    int getTimeToDisappear() const;
    
    void getTank() const;
    
private:
    Tank *tank;
    int timeToDisappear;
};


#endif
