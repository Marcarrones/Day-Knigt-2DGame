#ifndef _ENTITY_
#define _ENTITY_

#include "Sprite.h"
//#include "Position.h"
#include "CollisionBox.h"
#include "TileMap.h"
#include "ICollidable.h"
#include "ICollider.h"

// Base entity class, represents any object present in the scene

class Entity : public ICollidable 
{
public:
	CollisionBox collider;

	//Entity();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	
	virtual void update(int deltaTime);
	void render();

	// VISITOR PATTERN COLLISION
	virtual bool collidedBy(ICollider *collider) = 0;

	void setTileMap(TileMap *tileMap);
	
	void setPosition(const glm::vec2 &pos);
	glm::ivec2* getPos() { return &posEntity;  };

protected:
	virtual void initSprite(ShaderProgram &shaderProgram) = 0;
	Sprite *sprite;
	Texture spritesheet;
	TileMap *map;
	glm::ivec2 tileMapDispl, posEntity;
};

#endif // _ENTITY_INCLUDE