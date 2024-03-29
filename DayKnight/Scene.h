#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "MenuSuperior.h"
#include "StartEndDoor.h"
#include "Key.h"
#include "Clock.h"
#include "Health.h"
#include "Gema.h"
#define SCREEN_X 32
#define SCREEN_Y 16


// Scene contains all the entities of our game.
// It is responsible for updating and render them.

enum Level {
	Level01, Level02, Level03, Level04
};


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	
	void update(int deltaTime);
	void render();

	void showKey();
	void changelevel(Level newLevel);
	void restart();
	void finishLevel();

	void setGodModeOn();
private:
	void renderEntities();

	//void playerColisionWithEntity(const Enemy1 & other);

	void initEntities();
	void initShaders();
	void initSpriteBackground();


	string Scene::levelTxt(Level level) {
		switch (level) {
		case Level01: return "level01";
		case Level02: return "level02";
		case Level03: return "level03";
		case Level04: return "level04";
		}
		return "level01";
	}

private:
	TileMap *map;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	
	Level level, screen;
	
	Texture spritesheetBackground;
	Sprite *background;

	Player *player;
	Key *key;
	Clock *clock;
	StartEndDoor* startEndDoor;
	Gema *gema;
	Health *health;
	vector<Entity*> entites;
	
	MenuSuperior* menuSuperior;
	float cuentaAtras;
	int playerPoints,painTiles;
	bool inScreenKey,pickHealth,pickGem;
	bool debugMode = false;
};


#endif // _SCENE_INCLUDE

