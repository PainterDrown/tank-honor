#include "Base.hpp"

Base* Base::create(const bool isR) {
    Base *base = (Base*)new Base();
    if (!base) {
        return NULL;
    }
    base->isR = isR;
    string filename;
    if (isR) {
        filename = "pictures/R-base.png";
    } else {
        filename = "pictures/B-base.png";
    }
    base->initWithFile(filename);
    base->initAttributes();
    return base;
}

void Base::initAttributes() {
    health_value  = health_value_max = 2200;
    attack_value  = 0;
    defense_value = 220;
}

void Base::playDestroyAnimation() {
    string animationName;
    if (isR) animationName = "R-base-destroy";
    else     animationName = "B-base-destroy";
    auto aimation = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
    runAction(aimation);
}
