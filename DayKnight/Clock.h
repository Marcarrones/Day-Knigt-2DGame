#ifndef _CLOCK_INCLUDE
#define _CLOCK_INCLUDE

#include "Entity.h"
class Clock: public Entity
{
public:

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime) override;

	virtual bool collidedBy(ICollider *collider) override
		{ return collider->collideWith(this); }


	void StopTime();
	bool isStopTime();
	void pick();
	bool ispicked();


private:
	bool picked;
	float timeToStop;
	void initSprite(ShaderProgram &shaderProgram);
};

#endif