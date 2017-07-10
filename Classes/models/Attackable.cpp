#include "Attackable.hpp"

Attackable::Attackable() {
    health_value_label = Label::createWithTTF("[----------]", "fonts/fangzhengyunu.ttf", 10.0f);
    health_value_label->setColor(Color3B::GREEN);
}

int Attackable::getHealthValueMax() const {
    return health_value_max;
}

int Attackable::getHealthValue() const {
    return health_value;
}

int Attackable::getAttackValue() const {
    return attack_value;
}

int Attackable::getDefenseValue() const {
    return defense_value;
}

Label* Attackable::getHealthValueLabel() const {
    return health_value_label;
}

void Attackable::setHealthValueMax(const int v) {
    health_value_max = v;
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
    updateHealthValueLabel();
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

void Attackable::updateHealthValueLabel() {
//    float ratio = (float)health_value / (float)health_value_max;
//    
//    // 显示血条
//    if      (ratio > 0.9f) health_value_label->setString("[----------]");
//    else if (ratio > 0.8f) health_value_label->setString("[--------- ]");
//    else if (ratio > 0.7f) health_value_label->setString("[--------  ]");
//    else if (ratio > 0.6f) health_value_label->setString("[-------   ]");
//    else if (ratio > 0.5f) health_value_label->setString("[------    ]");
//    else if (ratio > 0.4f) health_value_label->setString("[-----     ]");
//    else if (ratio > 0.3f) health_value_label->setString("[----      ]");
//    else if (ratio > 0.2f) health_value_label->setString("[---       ]");
//    else if (ratio > 0.1f) health_value_label->setString("[--        ]");
//    else if (ratio > 0.0f) health_value_label->setString("[-         ]");
//    else                   health_value_label->setString("[          ]");
//    
//    // 显示血条颜色
//    if      (ratio > 0.67f) health_value_label->setColor(Color3B::GREEN);
//    else if (ratio > 0.33f) health_value_label->setColor(Color3B::ORANGE);
//    else if (ratio > 0.00f) health_value_label->setColor(Color3B::RED);
//    else                    health_value_label->setColor(Color3B::BLACK);
}
