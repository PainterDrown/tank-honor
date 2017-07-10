#ifndef ATTACKABLE
#define ATTACKABLE

#include "cocos2d.h"
#include "enums.hpp"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

class Attackable: public Sprite {
public:    
    int getHealthValueMax() const;
    
    int getHealthValue() const;
    
    int getAttackValue() const;
    
    int getDefenseValue() const;
    
    void setHealthValueMax(const int v);
    
    void setHealthValue(const int v);
    
    void setAttackValue(const int v);
    
    void setDefenseValue(const int v);

    void hurt(const int hurt);
    
    virtual void playDestroyAnimation() = 0;
    
    void destroy();
    
protected:
    int health_value_max;  // 生命值上限
    int health_value;      // 生命值
    int attack_value;      // 攻击力
    int defense_value;     // 防御力
};

#endif
