#ifndef _ENEMY1_
#define _ENEMY1_

#include "Entity.h"

class Enemy1 : public Entity
{
public:
	//Enemy1();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	
	void update(int deltaTime) override;
	void changeDirection();
	//void render();

	virtual bool collidedBy(ICollider *collider) override 
		{ return collider->collideWith(this); }


	void setTileMap(TileMap *tileMap);
	//void setPosition(const glm::vec2 &pos);

	int enemySpeed = 1;

private:
	void initSprite(ShaderProgram &shaderProgram);

	int movementDir = 1; // 1 -> Right : -1 -> Left
};

#endif /// _ENEMY1_