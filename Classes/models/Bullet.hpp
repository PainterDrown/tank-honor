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
    
    int calculateDamage(const Tank &tank) const;
    
    BULLET_STATE getState() const;
    
    void fly();
    
private:
    TANK_TYPE type;
    BULLET_STATE state;
    bool control;
    int attack_value;
    int attack_range;
    int bullet_speed;
};


#endif
