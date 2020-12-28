#include "QuadNode.h"
#include"Camera.h"
#include"Collision.h"
QuadNode::QuadNode()
{
}

void QuadNode::fillObjectsToCamera()
{
	auto camera = Camera::getInstance();
	if (LeftTop != NULL)
	{
		if (Collision::AABBCheck(camera, LeftTop))
		{
			LeftTop->fillObjectsToCamera();
		}

		if (Collision::AABBCheck(camera, RightTop))
		{
			RightTop->fillObjectsToCamera();
		}

		if (Collision::AABBCheck(camera, LeftBottom))
		{
			LeftBottom->fillObjectsToCamera();
		}

		if (Collision::AABBCheck(camera, RightBottom))
		{
			RightBottom->fillObjectsToCamera();
		}
	}
	else
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			auto obj = objects.at(i);
			if (!camera->allObjects->_Contain(obj))
			{
				camera->allObjects->_Add(obj);
				camera->objectCategories.at(obj->getCollisionType())->_Add(obj);
			}
		}
	}
}
