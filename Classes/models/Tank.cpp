#include "Tank.hpp"

Tank* Tank::create(const bool isR,
                   const TANK_TYPE type) {
    Tank *tank = new Tank();
    if (!tank) {
        return NULL;
    }
	tank->lowBlood = false;
	tank->isAmeetWall = false;
	tank->isAmeet = false;
    tank->isR = isR;
    tank->type = type;
    tank->bindImage();
    tank->initAttributes();
    tank->setState(TANK_STATE::NORMAL);
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
        default:
            return;
    }
}

TANK_TYPE Tank::getType() const {
    return type;
}

bool Tank::getIsR() const {
    return isR;
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

TANK_STATE Tank::getState() const {
    return state;
}

void Tank::setIsR(bool isr) {
    this->isR = isr;
}

void Tank::setType(TANK_TYPE type) {
    this->type = type;
}

void Tank::setState(TANK_STATE s) {
    state = s;
}

void Tank::destroy() {
    auto aimation = RepeatForever::create(Animate::create(
        AnimationCache::getInstance()->getAnimation("tank-boom")));
    runAction(aimation);
}

void Tank::move(const bool forward, const Wall *wall) {
    Vec2 nextPos;
    if (forward) {
        nextPos = Vec2(
            getPositionX() + 10 * sin(CC_DEGREES_TO_RADIANS(getRotation())),
            getPositionY() + 10 * cos(CC_DEGREES_TO_RADIANS(getRotation())));
    } else {
        nextPos = Vec2(
            getPositionX() - 10 * sin(CC_DEGREES_TO_RADIANS(getRotation())),
            getPositionY() - 10 * cos(CC_DEGREES_TO_RADIANS(getRotation())));
    }
    if (!wall->getBoundingBox().containsPoint(nextPos)) {
        auto moveToAction = MoveTo::create(0.1f, nextPos);
        runAction(moveToAction);
    }
}

void Tank::turn(const bool leftward) {
    if (leftward) {
        auto rotateAction = RotateBy::create(0.1f, -10);
        runAction(rotateAction);
    } else {
        auto rotateAction = RotateBy::create(0.1f, 10);
        runAction(rotateAction);
    }
}

void Tank::playDestroyAnimation() {
    auto aimation = Animate::create(AnimationCache::getInstance()->getAnimation("destroy-tank"));
    runAction(aimation);
}
