#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Text.h"
#include <string.h>

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
	startEndDoor = NULL;

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
	inScreenKey = false;
	
}


void Scene::restart()
{
	changelevel(level);
	return;
    /*	currentTime = 0.0f;
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
	inScreenKey = false;
	//startEndDoor = new StartEndDoor();
	//startEndDoor->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	//enemy = new Enemy1();
	//enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	//enemy->setPosition(glm::vec2(100, 50));
	*/
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
	player->update(deltaTime);

	background->update(deltaTime);
	menuSuperior->update(deltaTime);
	menuSuperior->updateTime(cuentaAtras/1000);
	menuSuperior->setPoints(playerPoints);
	
	// MOVER A GAME
	if (Game::instance().getKey(49)) {
		changelevel(Level01);
		
	}
	if (Game::instance().getKey(50)) {
		changelevel(Level02);
		
	}

	if (Game::instance().getKey(51)) {
		changelevel(Level03);
	}

	if (Game::instance().getKey(107)) {
		showKey();
	}
	
	if (Game::instance().getKey(105)) {
		player->changeImmune();
	}
	for (int i = 0; i < entites.size(); i++) {
		Entity* e = entites[i];

		e->update(deltaTime);

		e->collidedBy(player);
	}

	if (player->getlive() < 0) {
		// SE MAMO
		restart();
	}
	// Check if map cleared
	if (map->remainingTiles() <= 0) {
		// Visisbilidad llave
		startEndDoor->open();
		//finishLevel();
	}

	// Abrir puerta
	if (player->collideWith(key)) startEndDoor->open();
	

	if (startEndDoor->isOpenClose()) {
		//TODO: si esta abierto y la pos de jugador es igual que la puerta pasa a la siguiente pantalla
		player->collideWith(startEndDoor);
		
	}
	
	startEndDoor->update(deltaTime);
	key->update(deltaTime);
	clock->update(deltaTime);
	
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
    cuentaAtras = 60000.0f;
	map = TileMap::createTileMap("levels/" + levelTxt(newLevel) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

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
	//enemy->render();
}

void Scene::renderEntities() {
	player->render();

	for (int i = 0; i < entites.size(); i++) {
		entites[i]->render();
	}
	startEndDoor->render();

	// TODO: Mirar si todo el suelo est� pintado 
	if (inScreenKey){
		key->render();
	}


	clock->render();
}

#pragma endregion

#pragma region INIT


void Scene::initEntities() {
	if (map == nullptr) return;
	// Player
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
		Enemy* n = new Enemy(); // Cambiar a implementacion de Enemy1/Skeleton

		n->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		n->setPosition(positions.top());
		n->setTileMap(map);

		entites.push_back(n);
		positions.pop();
	}

	// Door pos


	startEndDoor = new StartEndDoor();
	startEndDoor->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	glm::vec2 exitPos = map->exitPos;
	exitPos.y += 16;
	exitPos.x += 16;
	// TODO: Revisar esto porque si no se a�ade 16 de altura se queda arriba
	startEndDoor->setPosition(exitPos);
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

