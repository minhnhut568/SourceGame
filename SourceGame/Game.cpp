#include "Game.h"
#include "AriseBase.h"
#include"Player.h"
#include"Scorebar.h"

/* singleton pattern */
Game* Game::instance = 0;
Game* Game::getInstance()
{
	if (instance == 0)
		instance = new Game();
	return instance;
}

/* Các câu lệnh khởi tạo game */
void Game::GameInit()
{
	/* khởi tạo tilemap */
	world = new World();
	world->Init("assets/levels/area2");

	overWorld = new OverWorld();
	overWorld->Init("assets/levels/area2_oneworld");

	worldIntro = new WorldIntro();

	worldEnd = new WorldEnd();

	Camera::getInstance()->setSize(
		/* kích thước của camera bằng với kích thước của backbuffer */
		GLOBALS_D("backbuffer_width"),
		GLOBALS_D("backbuffer_height"));


	// world
	/*worldType = WT_WORLD;
	world->setCurrentSpace(0);
	world->resetLocationInSpace();*/

	// over world
	//worldType = WT_OVER_WORLD_SPACE0;
	//overWorld->setCurrentSpace(3);
	//overWorld->resetLocationInSpace();

	 //intro
	worldType = WT_INTRO;

	//world end
	//worldType = WT_END;
	//worldEnd->start();

	//INTRO'S SOUND
	Sound::getInstance()->loadSound("Sound/Opening.wav", "Intro");
	Sound::getInstance()->loadSound("Sound/CarSplash.wav", "CarSplash");
	Sound::getInstance()->loadSound("Sound/CarBackground.wav", "CarBackground");
	Sound::getInstance()->loadSound("Sound/Ending.wav", "Ending");


	//AREA2'S SOUND
	Sound::getInstance()->loadSound("Sound/Area2.wav", "Area2");

	// PLAYER SOUND
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (7).wav", "PlayerFireArea2");
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (10).wav", "PlayerJump");
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (19).wav", "PlayerInjured");
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (21).wav", "PickingItems");
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (8).wav", "PlayerFireOverWorld");
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (4).wav", "BulletTouchBoss");
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (13).wav", "PlayerBulletHitBrick");


	//ENEMY'S SOUND
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (27).wav", "EnemyDie");
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (30).wav", "SkullFire");
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (22).wav", "TeleporterTransform");
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (15).wav", "MineBip");


	//BOSS
	Sound::getInstance()->loadSound("Sound/Boss.wav", "Boss");
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (35).wav", "BossDie");
	Sound::getInstance()->loadSound("Sound/Blaster Master SFX (9).wav", "BossFire");



	Sound::getInstance()->loadSound("Sources/Sound/rawSound/GameOver.wav", "GameOver");
	Sound::getInstance()->loadSound("Sources/Sound/rawSound/LifeLost.wav", "LifeLost");
	Sound::getInstance()->loadSound("Sources/Sound/rawSound/Blaster Master SFX (29).wav", "TankDie");
	Sound::getInstance()->loadSound("Sources/Sound/rawSound/Blaster Master SFX (22).wav", "Blink");
	Sound::getInstance()->loadSound("Sources/Sound/rawSound//Blaster Master SFX (17).wav", "Thunder");
	Sound::getInstance()->loadSound("Sources/Sound/Ending/Mountain.wav", "Mountain");
}
/* Các câu lệnh cập nhật game */
void Game::GameUpdate(float dt)
{
	switch (worldType)
	{
	case WT_INTRO:
		worldIntro->update();
		break;
	case WT_WORLD:
		world->update(dt);
		Sound::getInstance()->stop("Intro");
		Sound::getInstance()->play("Area2", true, 0);
		Sound::getInstance()->setVolume(90, "Area2");
		break;
	case WT_OVER_WORLD_SPACE0:
		overWorld->update(dt);
		Sound::getInstance()->play("Area2", true, 0);
		Sound::getInstance()->setVolume(90, "Area2");
		break;
	case WT_OVER_WORLD_SPACE1:
		overWorld->update(dt);
		break;
	case WT_OVER_WORLD_SPACE2:
		overWorld->update(dt);
		break;
	case WT_OVER_WORLD_SPACE4:
		overWorld->update(dt);
		break;
	case WT_END:
		Sound::getInstance()->stop("Area2");
		Sound::getInstance()->stop("Boss");
		Sound::getInstance()->play("Ending", true, 0);
		worldEnd->update();
		break;
	default:
		break;
	}

	AriseBase::updateAriseObjects(dt);
	Scorebar::getInstance()->update();
}
/* Các câu lệnh vẽ của game */
void Game::GameRender()
{
	switch (worldType)
	{
	case WT_INTRO:
		worldIntro->render();
		break;
	case WT_WORLD:
		world->render();
		Scorebar::getInstance()->render();
		break;
	case WT_OVER_WORLD_SPACE0:
		overWorld->render();
		Scorebar::getInstance()->render();
		break;
	case WT_OVER_WORLD_SPACE1:
		overWorld->render();
		Scorebar::getInstance()->render();
		break;
	case WT_OVER_WORLD_SPACE2:
		overWorld->render();
		Scorebar::getInstance()->render();
		break;
	case WT_OVER_WORLD_SPACE4:
		overWorld->render();
		Scorebar::getInstance()->render();
		break;
	case WT_END:
		worldEnd->render();
		break;
	default:
		break;
	}
}

WorldType Game::getWorldType()
{
	return worldType;
}

void Game::setWorldType(WorldType worldType)
{
	auto gameDirectx = GameDirectX::getInstance();
	this->worldType = worldType;
	switch (worldType)
	{
	case WT_INTRO:
		gameDirectx->backbufferWidth = 256;
		gameDirectx->backbufferHeight = 280;
		break;
	case WT_WORLD:
		gameDirectx->backbufferWidth = 240;
		gameDirectx->backbufferHeight = 224;
		break;
	case WT_END:
		gameDirectx->backbufferWidth = 258;
		gameDirectx->backbufferHeight = 224;
		break;
	case WT_OVER_WORLD_SPACE0:
	case WT_OVER_WORLD_SPACE1:
	case WT_OVER_WORLD_SPACE2:
	case WT_TO_WORLD_SPACE6:
	case WT_TO_WORLD_SPACE4:
	case WT_TO_WORLD_SPACE5:
	case WT_TO_WORLD_SPACE9:
		gameDirectx->backbufferWidth = 256;
		gameDirectx->backbufferHeight = 224;
	default:
		break;
	}


	Camera::getInstance()->setWidth(gameDirectx->backbufferWidth);
	Camera::getInstance()->setHeight(gameDirectx->backbufferHeight);
}

Game::Game()
{

}


Game::~Game()
{
}
