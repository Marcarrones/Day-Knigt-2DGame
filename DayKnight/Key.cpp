#include "Key.h"

enum {
	SHOW,
	PICKED
};

Key::Key()
{
}

void Key::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	Entity::init(tileMapPos, shaderProgram);
	initSprite(shaderProgram);
}

void Key::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void Key::render()
{
	Entity::render();
}

void Key::setTileMap(TileMap * tileMap)
{
	map = tileMap;
}

void Key::show()
{
	//Para no mostrar deja de hacer el render()
	sprite->changeAnimation(SHOW);
}

bool Key::isShow()
{
	return showing;
}

bool Key::isPicked()
{
	return pick;
}


Key::~Key()
{
}

void Key::initSprite(ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/Objetos/Key.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25,1 ), &spritesheet, &shaderProgram);

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
