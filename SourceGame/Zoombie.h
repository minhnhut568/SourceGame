#pragma once
#include "PhysicsObject.h"
/* lớp Zoombie để hiện thực lớp BaseObject */
class Zoombie :
	public PhysicsObject
{
public:
	void onCollision(MovableRect* other, float collisionTime, int nx, int ny) override;
	Zoombie();
	~Zoombie();
};

