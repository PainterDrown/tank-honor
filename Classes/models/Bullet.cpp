#include "Bullet.hpp"

static Bullet* Bullet::create(const TANK_TYPE type,
                      const int attack_value,
                      const int attack_range,
                      const int bullet_speed) {
    // 申请内存空间
    Bullet *bullet = new Bullet();
    if (!bullet) {
        return NULL;
    }
    
    // 绑定图片
    switch(type) {
        case TANK_TYPE::ASSASSIN:
            bullet->initWithFile("bullet-assassin.png");
            break;
        case TANK_TYPE::FIGHTER:
            bullet->initWithFile("bullet-fighter.png");
            break;
        case TANK_TYPE::SHOOTER:
            bullet->initWithFile("bullet-shooter.png");
            break;
        default:
            if (bullet) {
                delete bullet;
            }
            return NULL;
    }
    
    // 绑定属性
    bullet->type = type;
    bullet->attack_value = attack_value;
    bullet->attack_range = attack_range;
    bullet->bullet_speed = bullet_speed;
    
    return bullet;
}

int Bullet::calculateDamage(const Tank &tank) const {
    static const int BASE = 1024;
    return attack_value * (1 - (double)tank.getDefenseValue() / BASE);
}

BULLET_STATE Bullet::getState() const {
    return state;
}

void Bullet::fly() {
    
}
