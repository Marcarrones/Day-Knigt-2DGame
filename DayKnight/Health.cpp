#include "Health.h"


enum {
	SHOW,
	PICKED
};

Health::Health()
{
}

void Health::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	Entity::init(tileMapPos, shaderProgram);
	initSprite(shaderProgram);
	picked = false;
}

void Health::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void Health::render()
{
	Entity::render();
}


void Health::setTileMap(TileMap * tileMap)
{
	map = tileMap;
}

void Health::pick()
{
	picked = true;
}

bool Health::ispicked()
{
	return picked;
}

Health::~Health()
{
}

void Health::initSprite(ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/Objetos/VitalityPotion.png", TEXTURE_PIXEL_FORMAT_RGBA);
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
