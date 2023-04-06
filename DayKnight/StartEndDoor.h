#ifndef _START_END_DOOR_INCLUDE
#define _START_END_DOOR_INCLUDE

#include "Entity.h"

class StartEndDoor: public Entity
{

public:
	void update(int deltaTime) override;

	virtual bool collidedBy(ICollider *collider) override
		{ return collider->collideWith(this); }	

	void open();
	void close();

	bool isOpen();

private:
	void initSprite(ShaderProgram &shaderProgram);
	bool _isOpen;
};


#endif // _START_END_DOOR_INCLUDE
