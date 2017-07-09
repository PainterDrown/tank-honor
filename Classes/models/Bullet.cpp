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
        filename = "pictures/R-bullet-";
    else
        filename = "pictures/B-bullet-";
    switch (tank->getType()) {
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
            return NULL;
    }
    bullet->initWithFile(filename);
    
    return bullet;
}

void Bullet::testIfHit(Attackable *target) {
    if (target->getBoundingBox().containsPoint(getPosition())) {
        destroy();
        int damage = calculateDamage(target);
        target->hurt(damage);
    }
}

int Bullet::calculateDamage(const Attackable *target) const {
    static const int BASE_VALUE = 1024;
    return tank->getAttackValue() * (1 - (double)target->getDefenseValue() / BASE_VALUE);
}

void Bullet::destroy() {
    auto aimation = RepeatForever::create(Animate::create(
        AnimationCache::getInstance()->getAnimation("bullet-boom")));
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
