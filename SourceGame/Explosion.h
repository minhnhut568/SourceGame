#pragma once
#include "AriseBase.h"
class Explosion :
	public AriseBase
{
public:
	Explosion();
	static void setExplosion(BaseObject* obj);
	void onUpdate(float dt) override;
};

