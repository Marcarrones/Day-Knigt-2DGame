#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"
#include "Position.h"
#include "CollisionBox.h"
#include "TileMap.h"

// Base entity class, represents any object present in the scene

class Entity
{
public:
	CollisionBox collider;

	Entity();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	
	virtual void update(int deltaTime);
	void render();

	bool CheckCollision(Entity other);

	void setTileMap(TileMap *tileMap);
	
	void setPosition(const glm::vec2 &pos);
	glm::ivec2* getPos() { return &posEntity;  };

protected:
	Sprite *sprite;
	Texture spritesheet;
	TileMap *map;
	glm::ivec2 tileMapDispl, posEntity;
};

#endif // _ENTITY_INCLUDE