#include "Enemy.h"

#define FALL_STEP 4

enum EnemyAnims
{
	MOVE_RIGHT, MOVE_LEFT
};


void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	Entity::init(tileMapPos, shaderProgram);

	initSprite(shaderProgram);
}

void Enemy::initSprite(ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}

void Enemy::update(int deltaTime) {
	sprite->update(deltaTime);

	Edge edge = map->checkEdge(posEntity, glm::ivec2(32, 32));

	switch (movementDir) {
	case 1: // Right
		if (edge == Right || map->collisionMoveRight(posEntity, glm::ivec2(32, 32)) )
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


void Enemy::changeDirection() { 
	movementDir *= -1;
	sprite->changeAnimation(sprite->animation() == MOVE_LEFT ? MOVE_RIGHT : MOVE_LEFT);
}

void Enemy::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}
