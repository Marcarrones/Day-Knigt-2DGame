#ifndef _ENEMY_
#define _ENEMY_

#include "Entity.h"

class Enemy : public Entity
{
public:
	
	void changeDirection() { movementDir *= -1; };

	virtual bool collidedBy(ICollider *collider) override 
		{ return collider->collideWith(this); }

	int enemySpeed = 1;

protected:

	int movementDir = 1; // 1 -> Right : -1 -> Left
};

#endif /// _ENEMY1_