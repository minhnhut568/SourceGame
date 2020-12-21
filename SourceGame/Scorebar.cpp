#include "Scorebar.h"
#include"GameDirectX.h"
#include"Player.h"

Scorebar* Scorebar::instance = 0;
void Scorebar::decreaseHealth(int health)
{
	if (Player::getInstance() == Player::getPlayerMain())
	{
		if (curHealth - health == 0)
		{
			curHealth = 0;
		}
		curHealth = curHealth - health;
	}
	else
	{
		if (playerMiniCurHealth - health == 0)
		{
			playerMiniCurHealth = 0;
		}
		playerMiniCurHealth = playerMiniCurHealth - health;
	}
}
Scorebar* Scorebar::getInstance()
{
	if (instance == 0)
	{
		instance = new Scorebar();
	}
	return instance;
}

Scorebar::Scorebar()
{
	health = new GameTexture();
	health->Init("assets/sprites/misc/health.png");
	lostHealth = new GameTexture();
	lostHealth->Init("assets/sprites/misc/lost-health.png");
	maxHealth = S("max-health");
	playerMiniCurHealth = curHealth = maxHealth;
	healthLoccation = getHealthLocation();
}

POINT Scorebar::getHealthLocation()
{
	int relativeX = 16;
	int relativeY = 32;
	int screenHeight = GameDirectX::getInstance()->backbufferHeight;
	POINT pt;
	pt.x = relativeX;
	pt.y = screenHeight - relativeY - maxHealth * health->Height;
	return pt;
}

int Scorebar::getCurHealth()
{
	if (Player::getInstance() == Player::getPlayerMain())
	{
		return curHealth;
	}
	return playerMiniCurHealth;
}

void Scorebar::update()
{
}

void Scorebar::render()
{
	healthLoccation = getHealthLocation();
	int l_curHealth = getCurHealth();
	for (int i = maxHealth; i > 0; i--)
	{
		if (i > l_curHealth)
		{
			lostHealth->Render(healthLoccation.x, healthLoccation.y + (maxHealth - i) * health->Height);
		}
		else
		{
			health->Render(healthLoccation.x, healthLoccation.y + (maxHealth - i) * health->Height);
		}
	}
}
