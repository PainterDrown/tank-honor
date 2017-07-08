//#ifndef TANK
//#define TANK
//
//#include "TankHonor.hpp"
//#include "cocos2d.h"
//#include "SimpleAudioEngine.h"
//USING_NS_CC;
//using namespace CocosDenshion;
//using namespace std;
//class Bullet;
//class Tank;
//
//class Tank : public Sprite {
//public:
//	static Tank* create(const bool isR = true,
//		const TANK_TYPE type = TANK_TYPE::FIGHTER) {
//		Tank *tank = new Tank();
//		if (!tank) {
//			return NULL;
//		}
//		tank->isR = isR;
//		tank->type = type;
//		tank->bindImage();
//		tank->initAttributes();
//		tank->tankState = NORMAL;
//		return tank;
//	}
//
//	void bindImage() {
//		string filename = "pictures/";
//		if (isR) filename += "R-";
//		else filename += "B-";
//		switch (type) {
//		case TANK_TYPE::ASSASSIN:
//			filename += "assassin.png";
//			break;
//		case TANK_TYPE::FIGHTER:
//			filename += "fighter.png";
//			break;
//		case TANK_TYPE::SHOOTER:
//			filename += "shooter.png";
//			break;
//		default:
//			return;
//		}
//		initWithFile(filename);
//	}
//
//	void initAttributes() {
//		bullet_speed = 1;  // 1000/ms
//		switch (type) {
//		case TANK_TYPE::ASSASSIN:
//			health_value = 800;
//			attack_value = 200;
//			defense_value = 150;
//			attack_range = 1000;
//			moving_speed = 50;
//			break;
//		case TANK_TYPE::FIGHTER:
//			health_value = 1000;
//			attack_value = 150;
//			defense_value = 200;
//			attack_range = 700;
//			moving_speed = 40;
//			break;
//		case TANK_TYPE::SHOOTER:
//			health_value = 600;
//			attack_value = 100;
//			defense_value = 100;
//			attack_range = 1000;
//			moving_speed = 30;
//			break;
//		default:
//			return;
//		}
//	}
//
//	TANK_TYPE getType() const {
//		return type;
//	}
//
//	int getHealthValue() const {
//		return health_value;
//	}
//
//	int getAttackValue() const {
//		return attack_range;
//	}
//
//	int getDefenseValue() const {
//		return defense_value;
//	}
//
//	int getAttackRange() const {
//		return attack_range;
//	}
//
//	int getMovingSpeed() const {
//		return moving_speed;
//	}
//
//	int getBulletSpeed() const {
//		return bullet_speed;
//	}
//
//	TANK_STATE getTankState() const {
//		return tankState;
//	}
//
//	void setTankState(TANK_STATE s) {
//		tankState = s;
//	}
//
//	void hurt(Bullet* hitBullet) {
//		double damage = hitBullet->calculateDamage(*this);
//		if (health_value <= damage) {
//			this->tankState = DESTROYED;
//		}
//		else {
//			health_value -= damage;
//		}
//	}
//private:
//	bool isR;        // ̹��ʱR������B��
//	TANK_TYPE type;  // ̹�˵�����
//	TANK_STATE tankState; // ̹�˵�״̬
//
//	int health_value;    // ����ֵ
//	int attack_value;    // ������
//	int defense_value;   // ������
//	int attack_range;    // ���
//	int moving_speed;    // �ƶ��ٶ�
//	int bullet_speed;    // �ӵ��ٶ�
//
//						 // ��ǰ�ķ���x�᷽��Ϊ0�ȣ���ʱ�뷽��Ϊ��
//						 // һ��ʼR����̹��Ϊ0�ȣ�B����̹��Ϊ180��
//	int direction;
//};
//
//
//#endif
