#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy1.h"
#include "MenuSuperior.h"

#define SCREEN_X 32
#define SCREEN_Y 16


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	void changelevel(int level);
	void restar();
	void finishLevel(int level);

private:
	void initShaders();
	void initSpriteBackground();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int level, screen;
	Texture spritesheetBackground;
	Sprite *background;
	Enemy1 *enemy;
	MenuSuperior* menuSuperior;
	int playerPoints;
};


#endif // _SCENE_INCLUDE

