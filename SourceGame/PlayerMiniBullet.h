#pragma once
#include "PlayerBullet.h"
class PlayerMiniBullet :
	public PlayerBullet
{
public:
    PlayerMiniBullet();
	void onUpdate(float dt) override;
};

