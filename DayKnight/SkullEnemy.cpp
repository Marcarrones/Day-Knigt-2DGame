#include "SkullEnemy.h"


enum EnemyAnims
{
	MOVE_RIGHT, MOVE_LEFT
};

void SkullEnemy::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	tileMapDispl = tileMapPos;
	collider.init(&posEntity, 16, 16, &shaderProgram);

	initSprite(shaderProgram);
}

void SkullEnemy::update(int deltaTime) {
	sprite->update(deltaTime);

	
	switch (movementDir) {
	case 1: // Right
		if (map->collisionMoveRight(posEntity, glm::ivec2(16,16)))
			changeDirection();
		break;
	case -1: // Left
		if (map->collisionMoveLeft(posEntity, glm::ivec2(16,16)))
			changeDirection();
		break;
	}

	posEntity.x += enemySpeed*movementDir;

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}

void SkullEnemy::initSprite(ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/cabeza_volante.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16,16), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_RIGHT, 6);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.5f));
	//sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5, 0.0f));
	//sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}

void SkullEnemy::changeDirection() {
	Enemy::changeDirection();
	switch (movementDir) {
	case 1:
		sprite->changeAnimation(MOVE_RIGHT);
		break;
	case -1:
		sprite->changeAnimation(MOVE_LEFT);
		break;
	}
}