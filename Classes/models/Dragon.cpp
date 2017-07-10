#include "Dragon.hpp"

Dragon* Dragon::create(const bool isBig) {
    Dragon *dragon = new Dragon();
    if (!dragon) {
        return NULL;
    }
    dragon->isBig = isBig;
    string filename;
    if (isBig) {
        filename = "pictures/big-dragon.png";
    } else {
        filename = "pictures/small-dragon.png";
    }
    dragon->initWithFile(filename);
    dragon->initAttributes();
    return dragon;
}

void Dragon::initAttributes() {
    if (isBig) {
        health_value  = health_value_max = 8000;
        attack_value  = 400;
        defense_value = 400;
    } else {
        health_value  = health_value_max = 4000;
        attack_value  = 200;
        defense_value = 200;
    }
}

void Dragon::playDestroyAnimation() {
    string animationName;
    if (isBig) animationName = "big-dragon-destroy";
    else       animationName = "small-dragon-destroy";
    auto aimation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
    runAction(aimation);
}
