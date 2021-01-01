#include "AriseBase.h"
#include "Collision.h"
#include"Camera.h"

List<AriseBase*>* AriseBase::ariseObjects = 0;
List<AriseBase*>* AriseBase::getAriseObjects()
{
	if (AriseBase::ariseObjects == 0) {
		AriseBase::ariseObjects = new List<AriseBase*>();
	}
	return AriseBase::ariseObjects;
}

AriseBase::AriseBase()
{
	AriseBase::getAriseObjects()->_Add(this);
	inmortal = false;
}

void AriseBase::onUpdate(float dt)
{

	PhysicsObject::onUpdate(dt);

}

void AriseBase::updateAriseObjects(float dt)
{
	List<AriseBase*>* list = AriseBase::getAriseObjects();
	for (int i=0;i< list->Count;i++)
	{
		AriseBase* obj = list->at(i);
		obj->update(dt);

		Camera* camera = Camera::getInstance();

		if (!Collision::AABBCheck(camera, obj) && !obj->inmortal)
		{
			obj->markForDelete = true;
		}

		if (obj->markForDelete) {
			list->_Remove(obj);
			delete obj;
			i--;
		}
	}
}

void AriseBase::renderAriseObjects()
{
	List<AriseBase*>* list = AriseBase::getAriseObjects();
	for (int i = 0; i < list->Count; i++)
	{
		AriseBase* obj = list->at(i);
		obj->render();
	}
}
