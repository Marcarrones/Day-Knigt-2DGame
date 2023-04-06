#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Text.h"
#include <string.h>
#include "SkeletonEnemy.h"
#include "VampireEnemy.h"
#include "SkullEnemy.h"

// HACER GLOBALES?
//#define SCREEN_X 32
//#define SCREEN_Y 16

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
	
	changelevel(Level01);
	initSpriteBackground();
	
}


void Scene::restart()
{
	changelevel(level);
}

void Scene::finishLevel()
{
	switch (level) {
	case Level01:
		this->changelevel(Level02);
		break;
	case Level02:
		this->changelevel(Level03);
		break;
	case Level03:
		this->changelevel(Level04);
		break;
	case Level04:
		break;
	}
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	cuentaAtras -= deltaTime;
	if (cuentaAtras < 0.0) {
		restart();
	}
	player->update(deltaTime);

	background->update(deltaTime);
	menuSuperior->update(deltaTime);
	menuSuperior->updateTime(cuentaAtras/1000);
	menuSuperior->setPoints(playerPoints);
	startEndDoor->update(deltaTime);
	
	if (player->collideWith(clock)) {
		clock->pick();
		clock->StopTime();
	}

	if (Game::instance().getKey(111)) {
		startEndDoor->open();
	}

	for (int i = 0; i < entites.size(); i++) {
		Entity* e = entites[i];

		if (!clock->isStopTime()) {
			e->update(deltaTime);
		}
	

		// TODO: Si añades nuevos enemigos para que funcione la immnunidad 
		if (!player->isImmune()) {
			e->collidedBy(player);
		}
		
	}


	if (player->getlive() < 0) {
		// SE MAMO
		restart();
	}
	// Check if map cleared
	if (map->remainingTiles() <= 0 || inScreenKey == true) {
		// Visisbilidad llave
		key->show();
		inScreenKey = true;
	}
	
	// Abrir puerta
	if (player->collideWith(key) && inScreenKey == true) {
		startEndDoor->open();

	}
	
	// collideWithDoor ya detecta si esta abierta o no
	if (player->collideWith(startEndDoor)) {
		playerPoints += cuentaAtras * 100;
		finishLevel();
	}

	if (player->collideWith(health) && !pickHealth) {
		health->pick();
		int live = player->getlive();
		live += 1;
		player->changelive(live);
		pickHealth = true;
	}
	
	if (player->collideWith(gema) && !pickGem) {
		gema->pick();
		playerPoints += 500;
		pickGem = true;
	}

	// Para puntos
	int tmpPoint = painTiles - map->remainingTiles();
	painTiles = map->remainingTiles();
	playerPoints += tmpPoint*10;



	key->update(deltaTime);
	clock->update(deltaTime);
	gema->update(deltaTime);
	health->update(deltaTime);
	
	if (player->getlive() < 0) {
		restart();
	}
	
	menuSuperior->changeLive(player->getlive());
}

void Scene::showKey()
{
	inScreenKey = true;
}

void Scene::changelevel(Level newLevel)
{
	level = newLevel;
	currentTime = 0.0f;
    cuentaAtras = 120000.0f;
	map = TileMap::createTileMap("levels/" + levelTxt(newLevel) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	inScreenKey = false;
	debugMode = false;
	initEntities();
	menuSuperior = new MenuSuperior();
	menuSuperior->init(glm::ivec2(SCREEN_X + 16, SCREEN_Y + 32), texProgram);
	menuSuperior->changeLive(player->getlive());
}

#pragma region RENDER

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
}

void Scene::renderEntities() {
	player->showCollision = debugMode;
	player->render();

	for (int i = 0; i < entites.size(); i++) {
		entites[i]->showCollision = debugMode;
		entites[i]->render();
	}

	startEndDoor->showCollision = debugMode;
	startEndDoor->render();

	
	if (inScreenKey && !key->isPicked()){
		key->showCollision = debugMode;
		key->render();
	}

	if (!clock->ispicked()) {
		clock->showCollision = debugMode;
		clock->render();
	}

	if (!gema->ispicked() && !pickGem) {
		gema->showCollision = debugMode;
		gema->render();
	}
	
	if (!health->ispicked() && !pickHealth) {
		health->showCollision = debugMode;
		health->render();
	}


}

#pragma endregion

#pragma region INIT


void Scene::initEntities() {
	if (map == nullptr) return;
	// Player
	painTiles = map->remainingTiles();
	player = new Player();

	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(map->playerPos);
	player->setTileMap(map);
	playerPoints = 0;

	entites.clear();
	stack<glm::ivec2> positions;

	// Enemy 1

	positions = map->enemy1Pos;
	while(!positions.empty()) {
		Enemy* n = new SkeletonEnemy(); // Cambiar a implementacion de Enemy1/Skeleton

		n->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		n->setPosition(positions.top());
		n->setTileMap(map);

		entites.push_back(n);
		positions.pop();
	}

	// Enemy 2

	positions = map->enemy2Pos;
	while (!positions.empty()) {
		Enemy* n = new VampireEnemy();

		n->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		n->setPosition(positions.top());
		n->setTileMap(map);

		entites.push_back(n);
		positions.pop();
	}

	// Enemy 3
	positions = map->enemy3Pos;
	while (!positions.empty()) {
		Enemy* n = new SkullEnemy();

		n->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		n->setPosition(positions.top());
		n->setTileMap(map);

		entites.push_back(n);
		positions.pop();
	}

	// Door pos

	startEndDoor = new StartEndDoor();
	startEndDoor->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram); 
	startEndDoor->setPosition(map->exitPos);
	startEndDoor->setTileMap(map);


	// key pos 

	key = new Key();
	key->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	key->setPosition(map->keyPos);
	key->setTileMap(map);

	// Clock pos 

	clock = new Clock();
	clock->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	clock->setPosition(map->clockPos);
	clock->setTileMap(map);

	// Health pos 

	health = new Health();
	health->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	health->setPosition(map->healthPos);
	health->setTileMap(map);
	pickHealth = false;
	// Gem pos 

	gema = new Gema();
	gema->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	gema->setPosition(map->gemPos);
	gema->setTileMap(map);
	pickGem = false;

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

#pragma endregion

void Scene::setGodModeOn() {
	if (!debugMode) player->changeImmune();
	debugMode = true;
}
