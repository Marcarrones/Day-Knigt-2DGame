#ifndef _START_END_DOOR_INCLUDE
#define _START_END_DOOR_INCLUDE

#include "Entity.h"

class StartEndDoor:public Entity
{

public:
	~StartEndDoor();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime) override;
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	virtual bool collidedBy(ICollider *collider) override
		{ return collider->collideWith(this); }	
	void open();
	void close();
	glm::ivec2 getPosition();
	bool isOpenClose();
private:
	void initSprite(ShaderProgram &shaderProgram);

	glm::ivec2 tileMapDispl, posDoor;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	bool isOpen;
};


#endif // _START_END_DOOR_INCLUDE
