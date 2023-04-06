#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "StartEndDoor.h"
#include "Game.h"


enum DoorAnims
{
	CLOSED, OPENED
};

StartEndDoor::~StartEndDoor() {
	if (sprite != NULL)
		delete sprite;
}

void StartEndDoor::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	initSprite(shaderProgram);
	
}

void StartEndDoor::update(int deltaTime)
{
	sprite->update(deltaTime);
	//sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}

void StartEndDoor::render()
{
	sprite->render();
}

void StartEndDoor::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void StartEndDoor::setPosition(const glm::vec2& pos)
{

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x + 16), float(tileMapDispl.y + pos.y + 16)));
}


bool StartEndDoor::isOpenClose()
{
	return isOpen;
}

void StartEndDoor::initSprite(ShaderProgram &shaderProgram)
{
	sprite = new Sprite();
	spritesheet.loadFromFile("images/puerta_colores.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(CLOSED, 8);
	sprite->addKeyframe(CLOSED, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(OPENED, 8);
	sprite->addKeyframe(OPENED, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(CLOSED);
	isOpen = CLOSED;
	//sprite->setPosition(glm::vec2(float(tileMapDispl.x - posDoor.x), float(tileMapDispl.y - posDoor.y)));
	//sprite->setScale(glm::vec3(2.f, 2.f, 0.f));
}

void StartEndDoor::open() {
	sprite->changeAnimation(OPENED);
	isOpen = OPENED;
}

void StartEndDoor::close() {
	sprite->changeAnimation(CLOSED);
	isOpen = CLOSED;
}