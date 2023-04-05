#ifndef _CLOCK_INCLUDE
#define _CLOCK_INCLUDE

#include "Entity.h"
class Clock: public Entity
{
public:
	Clock();
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
	void render();
	void setTileMap(TileMap *tileMap);
	void StopTime();
	bool isStopTime();
	~Clock();

private:
	float timeToStop;
	void initSprite(ShaderProgram &shaderProgram);
};

#endif