#include "Bullet.hpp"

Bullet* Bullet::create(const TANK_TYPE type,
                       const bool isR,
                       const int attack_value,
                       const int attack_range,
                       const int bullet_speed) {
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
    
    return bullet;
}

int Bullet::calculateDamage(const Tank *tank) const {
    static const int BASE = 1024;
    return attack_value * (1 - (double)tank->getDefenseValue() / BASE);
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

}
