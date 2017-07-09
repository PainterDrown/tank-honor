#include "Bullet.hpp"

Bullet* Bullet::create(const TANK_TYPE type,
                       const bool isR,
                       const int attack_value,
                       const int attack_range,
                       const int bullet_speed,
                       const float rotation) {
    // 申请内存空间
    Bullet *bullet = new Bullet();
    if (!bullet) {
        return NULL;
    }
    bullet->autorelease();
    
    // 绑定图片
    string filename;
    if (isR)
        filename = "R-bullet-";
    else
        filename = "B-bullet-";
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
            return NULL;
    }
    bullet->initWithFile(filename);
    
    // 绑定属性
    bullet->type = type;
    bullet->attack_value = attack_value;
    bullet->attack_range = attack_range;
    bullet->bullet_speed = bullet_speed;
    
    // 设置方向
    bullet->setRotation(rotation);
    
    return bullet;
}

int Bullet::calculateDamage(const Tank *tank) const {
    static const int BASE_VALUE = 1024;
    return attack_value * (1 - (double)tank->getDefenseValue() / BASE_VALUE);
}

BULLET_STATE Bullet::getState() const {
    return state;
}

void Bullet::destroy() {
    auto aimation = RepeatForever::create(Animate::create(
        AnimationCache::getInstance()->getAnimation("bullet-boom")));
    runAction(aimation);
}

void Bullet::hit(Tank *tank) {
    destroy();
    int damage = calculateDamage(tank);
    tank->hurt(damage);
}

void Bullet::fly() {
    float time = attack_range / bullet_speed;
    auto moving = MoveBy::create(time,
        Vec2(attack_range * sin(CC_DEGREES_TO_RADIANS(getRotation()),
             attack_range * cos(CC_DEGREES_TO_RADIANS(getRotation())));
    runAction(moving);
}
