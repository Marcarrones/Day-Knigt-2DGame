#include "Gema.h"


enum {
	SHOW
};

Gema::Gema()
{
}

void Gema::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	Entity::init(tileMapPos, shaderProgram);
	initSprite(shaderProgram);
	picked = false;
}

void Gema::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void Gema::render()
{
	Entity::render();
}


void Gema::setTileMap(TileMap * tileMap)
{
	map = tileMap;
}

void Gema::pick()
{
	picked = true;
}

bool Gema::ispicked()
{
	return picked;
}

Gema::~Gema()
{
}

void Gema::initSprite(ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/Objetos/Gema.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1, 1), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(SHOW, 8);
	sprite->addKeyframe(SHOW, glm::vec2(0.f, 0.f));
	//sprite->addKeyframe(SHOW, glm::vec2(0.75f, 0.f));



	sprite->changeAnimation(SHOW);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}
