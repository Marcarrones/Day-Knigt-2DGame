#ifndef _ENEMY1_
#define _ENEMY1_

#include "Entity.h"

class Enemy1 : public Entity
{
public:
	Enemy1();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	
	virtual void update(int deltaTime);
	void changeDirection();
	void render();

	void setTileMap(TileMap *tileMap);
	//void setPosition(const glm::vec2 &pos);

	int enemySpeed = 3;

private:
	void initSprite(ShaderProgram &shaderProgram);

	int movementDir = 1; // 1 -> Right : -1 -> Left
};

#endif /// _ENEMY1_