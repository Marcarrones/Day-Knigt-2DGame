#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	Entity::init(tileMapPos, shaderProgram);
	bJumping = false;
	angle = 0.f;
	live = 3;
	immune = false;
	initSprite(shaderProgram);
	
}

void Player::initSprite(ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

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

void Player::update(int deltaTime)
{
	int lookingRight = 1;
	if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT) lookingRight = -1;
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{

		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posEntity.x -= 2;
		if (map->collisionMoveLeft(posEntity, glm::ivec2(32, 32)))
		{
			posEntity.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posEntity.x += 2;
		if (map->collisionMoveRight(posEntity, glm::ivec2(32, 32)))
		{
			posEntity.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}


	if (bJumping)
	{
		angle += deltaTime;

		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posEntity.y = startY;
		}
		else
		{
			posEntity.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posEntity, glm::ivec2(32, 32), &posEntity.y);
		}
	}
	else
	{
		angle += deltaTime;
		posEntity.y += FALL_STEP;
		if (map->collisionMoveDown(posEntity, glm::ivec2(32, 32), &posEntity.y))
		{
			angle = 0;
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posEntity.y;
			}
		}
	}
	//position->SetPos(posPlayer.x, posPlayer.y);
	paintTiles();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
	sprite->setAngle(lookingRight * (angle / 120));
}

void Player::render()
{
	Entity::render();
}


void Player::setPosition(const glm::vec2 &pos)
{
	posEntity = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}

int Player::getlive()
{
	return this->live;
}

void Player::changelive(int live)
{
	this->live = live;
}

bool Player::isImmune()
{
	return this->immune;
}

void Player::changeImmune()
{
	this->immune = !this->immune;
}


void Player::paintTiles() {
	map->paintBottomTile(posEntity, glm::ivec2(collider.getWidth(), collider.getHeight()));
	//map->paintBottomTile(posEntity, glm::ivec2(collider.getWidth(), collider.getHeight()), 2, 4);

}

