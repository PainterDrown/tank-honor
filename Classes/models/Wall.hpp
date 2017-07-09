#ifndef WALL
#define WALL

#include "cocos2d.h"
USING_NS_CC;

#include <string>
using namespace std;

class Wall: public Sprite {
public:
    Wall();
	static Wall* create();
	void bindImage();
};

#endif
