#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Text.h"


// #define SCREEN_X 32
// #define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 60
#define INIT_PLAYER_Y_TILES 288


Scene::Scene()
{
	map = NULL;
	player = NULL;
	menuSuperior = NULL;

}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	cuentaAtras = 60000.f;
	menuSuperior = new MenuSuperior();
	menuSuperior->init(glm::ivec2(SCREEN_X+16, SCREEN_Y+32), texProgram);
/*
	screen = 0;
	if (screen == 0) {
		changelevel(1);
		screen = 1;
	}
*/
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	level = 1;
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(map->playerPos);
	player->setTileMap(map);
	playerPoints = 0;
	menuSuperior->changeLive(player->getlive());

	initSpriteBackground();
	/*
	enemy = new Enemy1();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2(100, 50));
	*/
}


void Scene::restart()
{
	currentTime = 0.0f;
	menuSuperior = new MenuSuperior();
	menuSuperior->init(glm::ivec2(SCREEN_X + 16, SCREEN_Y + 32), texProgram);
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(map->playerPos));
	player->setTileMap(map);
	playerPoints = 0;
	menuSuperior->changeLive(player->getlive());
	cuentaAtras = 60000.f;
	//enemy = new Enemy1();
	//enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	//enemy->setPosition(glm::vec2(100, 50));
}

void Scene::finishLevel(int level)
{
	if (level == 1){
		changelevel(2);
	}
	else if (level == 2) {
		changelevel(3);
	}
	
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	cuentaAtras -= deltaTime;
	player->update(deltaTime);
	background->update(deltaTime);
	menuSuperior->update(deltaTime);
	menuSuperior->updateTime(cuentaAtras/1000);
	menuSuperior->setPoints(playerPoints);
	if (Game::instance().getKey(49)) {
		changelevel(1);
		
	}
	if (Game::instance().getKey(50)) {
		changelevel(2);
		
	}

	if (Game::instance().getKey(51)) {
		changelevel(3);
	}


	//if (player->collider.CheckColission(enemy->collider)) printf("COLISION!");

	// Check if map cleared
	if (map->remainingTiles() <= 0) {
		changelevel(2);
	}

}

// TODO: Remove duped function
/*
void Scene::changescreen(int screen) {
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
}
*/
// INIT LEVEL
void Scene::changelevel(int level)
{
	map = TileMap::createTileMap("levels/level0"+to_string(level)+".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	//player = new Player();
	//player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	menuSuperior->changeLevel(level);
	player->setPosition(map->playerPos);
	player->setTileMap(map);
	this->level = level;
	cuentaAtras = 60.f;

}


void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	background->render();
	map->render();
	menuSuperior->render();
	
	renderEntities();
	//enemy->render();
}

void Scene::renderEntities() {
	player->render();

}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::initSpriteBackground()
{
	spritesheetBackground.loadFromFile("images/level_background.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = new Sprite();
	background = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.0, 1.0), &spritesheetBackground, &texProgram);
	background->setNumberAnimations(1);

	background->setAnimationSpeed(0, 8);
	background->addKeyframe(0, glm::vec2(0.f, 0.f));

	background->changeAnimation(0);
	background->setPosition(glm::vec2(0, 0));
}



