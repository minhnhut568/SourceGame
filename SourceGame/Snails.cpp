#include "Snails.h"

Snails::Snails()
{
	setDirection(-1);
}

void Snails::onUpdate(float dt)
{
	setDx(getDirection());
}

void Snails::onCollision(MovableRect* other, float collisionTime, int nx, int ny)
{
	
}
