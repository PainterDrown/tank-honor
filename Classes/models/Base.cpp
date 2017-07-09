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
    health_value  = 2200;
    attack_value  = 0;
    defense_value = 220;
}
