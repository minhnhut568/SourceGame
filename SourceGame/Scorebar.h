#pragma once
#include"GameTexture.h"
class Scorebar
{
private:
	GameTexture* health,* lostHealth;
	POINT healthLoccation;
	int maxHealth, curHealth, playerMiniCurHealth;
public:
	void decreaseHealth(int health);
	static Scorebar* instance;
	static Scorebar* getInstance();
	Scorebar();
	POINT getHealthLocation();
	int getCurHealth();
	void update();
	void render();
};

