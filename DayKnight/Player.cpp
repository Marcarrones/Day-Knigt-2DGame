#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 60 // 48
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, AIRBOURNE
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
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.25f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));

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

	sprite->setAnimationSpeed(AIRBOURNE, 8);
	sprite->addKeyframe(AIRBOURNE, glm::vec2(.25f, .75f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}

#pragma region Collisions

bool Player::collidedBy(ICollider *collider) {
	// Es "impossible" que un collider (Player) colisione con esta instancia de Entity (AKA PLAYER)
	return false;
}

bool Player::collideWith(Enemy *other) {
	if (collider.CheckColission(other->collider)) {
		damagePlayer();
		return true;
	}
	return false;
}

bool Player::collideWith(Key * other)
{
	return collider.CheckColission(other->collider);
}

bool Player::collideWith(Clock * other)
{
	return collider.CheckColission(other->collider);
}

bool Player::collideWith(StartEndDoor * other)
{
	return collider.CheckColission(other->collider);
}

bool Player::collideWith(Gema * other)
{
	return collider.CheckColission(other->collider);
}
#pragma endregion

bool Player::collideWith(Health * other)
{
	return collider.CheckColission(other->collider);
}



void Player::update(int deltaTime)
{

	if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT) lookingRight = -1;
	if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT) lookingRight = 1;
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{

		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posEntity.x -= playerSpeed;
		if(map->collisionMoveLeft(posEntity, glm::ivec2(32, 32)))
		{
			posEntity.x += playerSpeed;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posEntity.x += playerSpeed;
		if(map->collisionMoveRight(posEntity, glm::ivec2(32, 32)))
		{
			posEntity.x -= playerSpeed;
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
		sprite->changeAnimation(AIRBOURNE);
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posEntity.y = startY;
		}
		else
		{
			posEntity.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posEntity, glm::ivec2(32, 32), &posEntity.y);
		}
	}
	else
	{
		angle += deltaTime;
		posEntity.y += FALL_STEP;
		if(map->collisionMoveDown(posEntity, glm::ivec2(32, 32), &posEntity.y))
		{
			angle = 0;
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posEntity.y;
			}
			if (sprite->animation() == AIRBOURNE)
			(lookingRight == 1) ? sprite->changeAnimation(STAND_RIGHT) : sprite->changeAnimation(STAND_LEFT);
		}
		else sprite->changeAnimation(AIRBOURNE);
	}
	//position->SetPos(posPlayer.x, posPlayer.y);
	paintTiles();
	if (map->checkSpike(posEntity, glm::ivec2(32, 32) ) && !immune) {
		damagePlayer();
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
	sprite->setAngle(lookingRight * (angle / 120));
}

void Player::damagePlayer() {
	live--;
	setPosition(map->playerPos);
}

void Player::setPosition(const glm::vec2 &pos)
{
	posEntity = pos;
	startY = posEntity.y;
	bJumping = false;
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
	immune = !immune;
}


void Player::paintTiles() {
	map->paintBottomTile(posEntity, glm::ivec2(collider.getWidth(), collider.getHeight()));
}

