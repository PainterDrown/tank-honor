#ifndef TANK
#define TANK

#include "cocos2d.h"
#include "enums.hpp"
#include "Attackable.hpp"
#include "Bullet.hpp"
#include "Wall.hpp"
#include "Tower.hpp"
#include <string>
USING_NS_CC;
using namespace std;

class Tank: public Attackable {
public:
    static Tank* create(const bool isR = true,
                        const TANK_TYPE type = TANK_TYPE::FIGHTER);
    
    void bindImage();
    
	void initAttributes();
    
    TANK_TYPE getType() const;
    
    bool getIsR() const;
    
    int getAttackRange() const;
    
    int getMovingSpeed() const;
    
    int getBulletSpeed() const;
    
    int getCD() const;
    
    TANK_STATE getState() const;
    
    void setIsR(bool isr);
    
    void setType(TANK_TYPE type);
    
    void setState(TANK_STATE s);
    
    void setCD(const int CD);
    
    void move(const bool forward, const Wall *wall, Label *label, const Tower *tower);
    
    void turn(const bool leftward);
    
    void playDestroyAnimation();

	void avoidWall(bool, const Wall*); //坦克被墙弹开
    
    bool withinAttackRange(const Attackable *target);
    
    bool isAmeetBase; 

	bool isAmeet;   //AI是否遇到敌方坦克
    
	bool isAmeetWall; //AI是否遇到墙壁
    
	bool lowBlood;    //AI是否低血，以300为止
    
protected:
    bool isR;        // 坦克时R方还是B方
    TANK_TYPE type;  // 坦克的类型
    TANK_STATE state; // 坦克的状态

    int attack_range;    // 射程
    int moving_speed;    // 移动速度
    int bullet_speed;    // 子弹速度
    int CD;              // 技能冷却时间
};

#endif
