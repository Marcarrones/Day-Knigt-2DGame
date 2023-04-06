#include "SkeletonEnemy.h"

#define FALL_STEP 4

enum EnemyAnims
{
	MOVE_RIGHT, MOVE_LEFT
};

void SkeletonEnemy::update(int deltaTime) {
	sprite->update(deltaTime);

	Edge edge = map->checkEdge(posEntity, glm::ivec2(32, 32));

	switch (movementDir) {
	case 1: // Right
		if (edge == Right || map->collisionMoveRight(posEntity, glm::ivec2(32, 32)))
			changeDirection();
		break;
	case -1: // Left
		if (edge == Left || map->collisionMoveLeft(posEntity, glm::ivec2(32, 32)))
			changeDirection();
		break;
	}

	posEntity.x += enemySpeed*movementDir;

	posEntity.y += FALL_STEP;

	map->collisionMoveDown(posEntity, glm::ivec2(32, 32), &posEntity.y);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}

void SkeletonEnemy::initSprite(ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/esqueleto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_RIGHT, 3);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.f));
	//sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_LEFT, 3);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5, 0.5f));
	//sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}

void SkeletonEnemy::changeDirection() {
	Enemy::changeDirection();
	switch (movementDir){
	case 1:
		sprite->changeAnimation(MOVE_RIGHT);
		break;
	case -1:
		sprite->changeAnimation(MOVE_LEFT);
		break;
	}
}