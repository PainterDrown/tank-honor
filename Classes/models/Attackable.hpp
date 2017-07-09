#ifndef ATTACKABLE
#define ATTACKABLE

#include "cocos2d.h"
#include "enums.hpp"
USING_NS_CC;

class Attackable: public Sprite {
public:    
    int getHealthValue() const;
    
    int getAttackValue() const;
    
    int getDefenseValue() const;
protected:
    int health_value;    // 生命值
    int attack_value;    // 攻击力
    int defense_value;   // 防御力
};

#endif
