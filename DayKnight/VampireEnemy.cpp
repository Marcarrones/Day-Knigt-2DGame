#include "VampireEnemy.h"

#define FALL_STEP 4

enum VAMP_ANIMS {
	MOVE_LEFT, MOVE_RIGHT,FLY,TRANSFORM
};


void VampireEnemy::update(int deltatime)
{
	if (currentCD <= 0 && !transforming) {
		// Start transformation
		sprite->changeAnimation(TRANSFORM);
		transforming = true;
		return;
	}

	currentCD -= deltatime;

	if (transforming) {
		// End transformation
		transformDur += deltatime;
		if (transformDur > 2000) {
			transform();
		}
	}
	else if (currentState == VAMPIRE) vampireUpdate(deltatime);
	else if (currentState == BAT) batUpdate(deltatime);


	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
	sprite->update(deltatime);
}

void VampireEnemy::initSprite(ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/ia_blue.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(FLY, 8);
	sprite->addKeyframe(FLY, glm::vec2(0.f, 0.75f));
	sprite->addKeyframe(FLY, glm::vec2(0.25f, 0.75f));


	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.75f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f, 0.f));

	sprite->setAnimationSpeed(TRANSFORM, 2);
	sprite->addKeyframe(TRANSFORM, glm::vec2(.0f, .5f));
	sprite->addKeyframe(TRANSFORM, glm::vec2(.25f, .5f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}


void VampireEnemy::changeDirection()
{
	Enemy::changeDirection();
	if (currentState == VAMPIRE) {
		switch (movementDir) {
		case 1:
			sprite->changeAnimation(MOVE_RIGHT);
			break;
		case -1:
			sprite->changeAnimation(MOVE_LEFT);
			break;
		}
	}
	else {

	}
}

void VampireEnemy::transform()
{
	currentState = (currentState == VAMPIRE) ? BAT : VAMPIRE;
	currentCD = transformCD*(rand()%2+1);
	transformDur = 0;
	transforming = false;
	if (currentState == BAT) {
		sprite->changeAnimation(FLY);
		posEntity.x -= posEntity.x%map->getTileSize();
		posEntity.y -= posEntity.y%map->getTileSize();
	}
	else {
		if (movementDir == -1) sprite->changeAnimation(MOVE_LEFT);
		else sprite->changeAnimation(MOVE_RIGHT);
	}
}


void VampireEnemy::vampireUpdate(int deltaTime) {
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
}


void VampireEnemy::batUpdate(int deltaTime) {

	if (map->collisionMoveDown(posEntity, glm::ivec2(32, 32), &posEntity.y) 
	|| map->collisionMoveUp(posEntity, glm::ivec2(32, 32), &posEntity.y))
		vertDirection *= -1;

	if (map->collisionMoveLeft(posEntity, glm::ivec2(32, 32)) 
	|| map->collisionMoveRight(posEntity, glm::ivec2(32, 32))) 
		changeDirection();
	
	posEntity.x += horSpeed*movementDir;
	posEntity.y += vertSpeed*vertDirection;
}