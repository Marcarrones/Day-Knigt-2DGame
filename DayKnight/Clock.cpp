#include "Clock.h"

enum {
	SHOW,
	PICKED
};

Clock::Clock()
{
}

void Clock::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	Entity::init(tileMapPos, shaderProgram);
	initSprite(shaderProgram);
	timeToStop = 0.0;
}

Clock::~Clock()
{
}

void Clock::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (timeToStop > 0.0) {
		timeToStop -= deltaTime;
	}
	else {
		timeToStop = 0.0;
	}
}

void Clock::render()
{
	Entity::render();
}

void Clock::setTileMap(TileMap * tileMap)
{
	map = tileMap;
}

void Clock::StopTime()
{
	timeToStop = 5000.0f;
}

bool Clock::isStopTime()
{
	return timeToStop != 0.0;
}


void Clock::initSprite(ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/Objetos/Clock.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(SHOW, 8);
	sprite->addKeyframe(SHOW, glm::vec2(0.f, 0.f));
	//sprite->addKeyframe(SHOW, glm::vec2(0.75f, 0.f));

	sprite->setAnimationSpeed(PICKED, 8);
	sprite->addKeyframe(PICKED, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(PICKED, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(PICKED, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(SHOW);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}