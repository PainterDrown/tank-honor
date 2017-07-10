#include "Bullet.hpp"

Bullet* Bullet::create(Tank *tank) {
    // 申请内存空间
    Bullet *bullet = new Bullet();
    if (!bullet) {
        return NULL;
    }
    bullet->autorelease();
    
    bullet->tank = tank;
    
    // 绑定图片
    string filename;
    if (tank->getIsR())
        filename = "pictures/R-";
    else
        filename = "pictures/B-";
    switch (tank->getType()) {
        case TANK_TYPE::ASSASSIN:
            filename += "assassin-bullet.png";
            break;
        case TANK_TYPE::FIGHTER:
            filename += "fighter-bullet.png";
            break;
        case TANK_TYPE::SHOOTER:
            filename += "shooter-bullet.png";
            break;
        default:
            return NULL;
    }
    bullet->initWithFile(filename);
    
    return bullet;
}

bool Bullet::testIfHit(Attackable *target) {
    if (target->getBoundingBox().containsPoint(getPosition())) {
        int damage = calculateDamage(target);
        target->hurt(damage);
        if (target->getHealthValue() <= 0) {
            tank->setHealthValueMax(tank->getHealthValueMax() + 200);
            tank->setAttackValue(tank->getAttackValue() + 100);
            tank->setDefenseValue(tank->getDefenseValue() + 100);
        }
        destroy();
        return true;
    } else {
        return false;
    }
}

int Bullet::calculateDamage(const Attackable *target) const {
    static const int BASE_VALUE = 1024;
    return tank->getAttackValue() * (1 - (double)target->getDefenseValue() / BASE_VALUE);
}

void Bullet::destroy() {
    string animationName;
    if (tank->getIsR()) {
        animationName = "R-bullet-destroy";
    } else {
        animationName = "B-bullet-destroy";
    }
    auto aimation = Animate::create(
        AnimationCache::getInstance()->getAnimation(animationName));
    runAction(aimation);
    SimpleAudioEngine::getInstance()->playEffect("sounds/fire.mp3", false);
    removeFromParentAndCleanup(true);
}

void Bullet::fly(const int timer) {
    float duration = (float)tank->getAttackRange() / (float)tank->getBulletSpeed() / 1000.0f;
    timeToDisappear = timer + duration * 10;
    float x = tank->getAttackRange() * sin(CC_DEGREES_TO_RADIANS(getRotation()));
    float y = tank->getAttackRange() * cos(CC_DEGREES_TO_RADIANS(getRotation()));
    auto moving = MoveBy::create(duration, Vec2(x, y));
    runAction(moving);
}

int Bullet::getTimeToDisappear() const {
    return timeToDisappear;
}

Tank* Bullet::getTank() const {
    return tank;
}
