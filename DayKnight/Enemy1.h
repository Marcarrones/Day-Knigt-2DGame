#ifndef _ENEMY1_
#define _ENEMY1_

#include "Entity.h"

class Enemy1 : public Entity
{
public:
	Enemy1();
	~Enemy1();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	
	virtual void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

private:
	void initSprite(ShaderProgram &shaderProgram);
};

#endif /// _ENEMY1_