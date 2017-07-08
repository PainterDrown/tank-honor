#ifndef ENUMS
#define ENUMS

enum TANK_STATE {
    NORMAL,     // 正常状态，不用进行特殊处理
    ATTACKING,  // 正要发动攻击，检测到时要播放进攻动画
    DESTROYED   // 生命值为0时触发这个状态，播放爆炸动画
};

enum TANK_TYPE {
    ASSASSIN,  // 刺客：血量中，伤害力高，防御力中，射程短，速度高，子弹速度中
    FIGHTER,   // 战士：血量高，伤害力中，防御力高，射程中，速度中，子弹速度低
    SHOOTER,   // 射手：血量低，伤害力低，防御力低，射程长，速度低，子弹速度高
    BASE       // 基地：血量高，无伤害力，防御力高，无射程，无速度，无子弹（莫名的基地型坦克）
};

enum BULLET_STATE {
    WAITING,
    FLYING
};

#endif
