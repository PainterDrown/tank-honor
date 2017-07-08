#include "Wall.hpp"

Wall::Wall() {}

Wall* Wall::create() {
	Wall *wall = new Wall();
	if (!wall) {
		return NULL;
	}
	wall->bindImage();
	return wall;
}

void Wall::bindImage() {
	string name = "pictures/wall.png";
	initWithFile(name);
}