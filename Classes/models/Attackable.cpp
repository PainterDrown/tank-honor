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

void Attackable::hurt(const int damage) {
    health_value -= damage;
    if (health_value <= 0) {
        health_value = 0;
        destroy();
    }
}
