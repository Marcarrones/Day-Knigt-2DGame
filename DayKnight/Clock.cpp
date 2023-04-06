#include "Clock.h"

enum {
	SHOW,
	PICKED
};



void Clock::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	tileMapDispl = tileMapPos;
	collider.init(&posEntity, 16, 16, &shaderProgram);
	initSprite(shaderProgram);
	timeToStop = 0.0;
	picked = false;
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


void Clock::StopTime()
{
	timeToStop = 5000.0f;
}

bool Clock::isStopTime()
{
	return timeToStop != 0.0;
}

void Clock::pick()
{
	sprite->changeAnimation(PICKED);
	picked = true;
}

bool Clock::ispicked()
{
	return picked;
}


void Clock::initSprite(ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/Objetos/Clock.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16,16), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);

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