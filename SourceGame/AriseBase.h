#pragma once
#include "PhysicsObject.h"

class AriseBase :
	public PhysicsObject
{
private:
	static List<AriseBase*>* ariseObjects;
protected:
	bool markForDelete;
public:
	static List<AriseBase*>* getAriseObjects();

	AriseBase();

	void onUpdate(float dt) override;


	static void updateAriseObjects(float dt);

	static void renderAriseObjects();
};
