#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player:public Entity
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	
private:
	bool bJumping;
	//glm::ivec2 tileMapDispl, posPlayer;
	float angle;
	int jumpAngle, startY;
	//Texture spritesheet;
	//Sprite *sprite;
	//TileMap *map;
	void initSprite(ShaderProgram &shaderProgram);

};


#endif // _PLAYER_INCLUDE


