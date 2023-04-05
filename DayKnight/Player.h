#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"
#include "Enemy1.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player : public Entity, public ICollider
{

public:
	//Player();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime) override;
	void render();
	
	//Necesario pero inutil (ICollidable de Entity)
	virtual bool collidedBy(ICollider * collider) override;
	
	// Implementacion ICollider
	virtual bool collideWith(Enemy1 *other) override;
	virtual bool collideWith(Key *other) override;
	virtual bool collideWith(Clock *other) override;
	virtual bool collideWith(StartEndDoor *other) override;

	//void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	
	int getlive();
	void changelive(int live);
	bool isImmune();
	void changeImmune();


	int playerSpeed = 2;
	
private:
	bool bJumping;
	//glm::ivec2 tileMapDispl, posPlayer;
	float angle;
	int jumpAngle, startY;
	//Texture spritesheet;
	//Sprite *sprite;
	//TileMap *map;
	void initSprite(ShaderProgram &shaderProgram);
	void paintTiles();
	int live;
	bool immune;
};


#endif // _PLAYER_INCLUDE


