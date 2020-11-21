#include "Zoombie.h"



Zoombie::Zoombie()
{
}

void Zoombie::onCollision(MovableRect * other, float collisionTime, int nx, int ny)
{
	/* ngăn chặn di chuyển */
	preventMovementWhenCollision(collisionTime, nx, ny);
	PhysicsObject::onCollision(other, collisionTime, nx, ny);
}


Zoombie::~Zoombie()
{
}
