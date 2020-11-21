#include "Gate.h"
#include "Player.h"

void Gate::onAABBCheck(MovableRect* other)
{
	if (other == Player::getInstance())
	{
		int nextSpace = atoi(customProperties["NextSpace"].c_str());
		int playerX = atoi(customProperties["PlayerX"].c_str());
		int playerY = world->getTileMap()->getWorldHeight() - atoi(customProperties["PlyerY"].c_str());
		int cameraX = atoi(customProperties["CameraX"].c_str());
		int cameraY = world->getTileMap()->getWorldHeight() - atoi(customProperties["CameraY"].c_str());

		world->setCurrentSpace(nextSpace);
		world->changeSpaceCameraX = cameraX;
		world->changeSpaceCameraY = cameraY;
		world->changeSpacePlayerX = playerX;
		world->changeSpacePlayerY = playerY;
		world->changeSpace = CHANGE_SPACE::CHANGE_SPACE_START;
	}
}
