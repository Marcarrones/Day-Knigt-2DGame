#ifndef _CLOCK_INCLUDE
#define _CLOCK_INCLUDE

#include "Entity.h"
class Clock: public Entity
{
public:
	Clock();
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime) override;
	void render();
	virtual bool collidedBy(ICollider *collider) override
		{ return collider->collideWith(this); }

	void setTileMap(TileMap *tileMap);
	void StopTime();
	bool isStopTime();
	~Clock();

private:
	float timeToStop;
	void initSprite(ShaderProgram &shaderProgram);
};

#endif