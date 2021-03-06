#include "Tower.hpp"

Tower* Tower::create(const bool isR) {
    Tower *tower = new Tower();
    if (!tower) {
        return NULL;
    }
    tower->isR = isR;
    string filename;
    if (isR) {
        filename = "pictures/R-tower.png";
    } else {
        filename = "pictures/B-tower.png";
    }
    tower->initWithFile(filename);
    tower->initAttributes();
    return tower;
}

void Tower::initAttributes() {
    health_value  = health_value_max = 2200;
    attack_value  = 0;
    defense_value = 220;
}

void Tower::playDestroyAnimation() {
    string animationName;
    if (isR) animationName = "R-tower-destroy";
    else     animationName = "B-tower-destroy";
    auto aimation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
    runAction(aimation);
}
