#include "Attackable.hpp"

int Attackable::getHealthValue() const {
    return health_value;
}

int Attackable::getAttackValue() const {
    return attack_value;
}

int Attackable::getDefenseValue() const {
    return defense_value;
}

void Attackable::setHealthValue(const int v) {
    health_value = v;
}

void Attackable::setAttackValue(const int v) {
    attack_value = v;
}

void Attackable::setDefenseValue(const int v) {
    defense_value = v;
}

void Attackable::hurt(const int damage) {
    health_value -= damage;
    if (health_value <= 0) {
        health_value = 0;
        destroy();
    }
}

void Attackable::destroy() {
    playDestroyAnimation();
    SimpleAudioEngine::getInstance()->playEffect("sounds/destroy.mp3", false);
    removeFromParentAndCleanup(true);
}
