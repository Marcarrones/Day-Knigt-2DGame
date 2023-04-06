#include "Key.h"

enum {
	SHOW,
	PICKED
};


void Key::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	tileMapDispl = tileMapPos;
	collider.init(&posEntity, 16, 16, &shaderProgram);
	initSprite(shaderProgram);
}

void Key::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void Key::render()
{
	if ((showing && !pick) || !pick )
	Entity::render();
}


void Key::show()
{
	//Para no mostrar deja de hacer el render()
	sprite->changeAnimation(SHOW);
	showing = true;
}

void Key::pickUp() {
	sprite->changeAnimation(PICKED);
	pick = true;
}

bool Key::isPicked()
{
	return pick;
}


void Key::initSprite(ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/Objetos/Key.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16,16), glm::vec2(0.25,1 ), &spritesheet, &shaderProgram);

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
