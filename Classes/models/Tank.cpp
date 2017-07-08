#include "Tank.hpp"

static Tank* Tank::create(const bool isR = true,
                    const TANK_TYPE type = TANK_TYPE::FIGHTER) {
    Tank *tank = new Tank();
    if (!tank) {
        return NULL;
    }
    tank->isR = isR;
    tank->type = type;
    tank->bindImage();
    tank->initAttributes();
    tank->setTankState(TANK_TYPE::NORMAL);
    return tank;
}

void Tank::bindImage() {
    string filename = "pictures/";
    if (isR) filename += "R-";
    else filename += "B-";
    switch (type) {
        case TANK_TYPE::ASSASSIN:
            filename += "assassin.png";
            break;
        case TANK_TYPE::FIGHTER:
            filename += "fighter.png";
            break;
        case TANK_TYPE::SHOOTER:
            filename += "shooter.png";
            break;
        case TANK_TYPE::BASE:
            filename += "base.png";
        default:
            return;
    }
    initWithFile(filename);
}

void Tank::initAttributes() {
    bullet_speed = 1;  // 1000/ms
    switch(type) {
        case TANK_TYPE::ASSASSIN:
            health_value  = 800;
            attack_value  = 200;
            defense_value = 150;
            attack_range  = 1000;
            moving_speed  = 50;
            break;
        case TANK_TYPE::FIGHTER:
            health_value  = 1000;
            attack_value  = 150;
            defense_value = 200;
            attack_range  = 700;
            moving_speed  = 40;
            break;
        case TANK_TYPE::SHOOTER:
            health_value  = 600;
            attack_value  = 100;
            defense_value = 100;
            attack_range  = 1000;
            moving_speed  = 30;
            break;
        case TANK_TYPE::BASE:
            health_value  = 2200;
            attack_value  = 0;
            defense_value = 220;
            attack_range  = 0;
            moving_speed  = 0;
        default:
            return;
    }
}

TANK_TYPE Tank::getType() const {
    return type;
}

int Tank::getHealthValue() const {
    return health_value;
}

int Tank::getAttackValue() const {
    return attack_range;
}

int Tank::getDefenseValue() const {
    return defense_value;
}

int Tank::getAttackRange() const {
    return attack_range;
}

int Tank::getMovingSpeed() const {
    return moving_speed;
}

int Tank::getBulletSpeed() const {
    return bullet_speed;
}

TANK_STATE Tank::getTankState() const {
    return tankState;
}

void Tank::setIsR(bool isr) {
    this->isR = isr;
}

void Tank::setType(TANK_TYPE type) {
    this->type = type;
}

void Tank::setTankState(TANK_STATE s) {
    tankState = s;
}

void Tank::hurt(const int damage) {
    health_value -= damage;
    if (health_value <= 0) {
        health_value = 0;
        destroy();
    }
}

void Tank::destroy() {
    auto aimation = RepeatForever::create(Animate::create(
        AnimationCache::getInstance()->getAnimation("tank-boom")));
    // aimation->setTag(11);
    runAction(aimation);
}
