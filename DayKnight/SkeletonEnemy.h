#ifndef _SKELETONENEMY_
#define _SKELETONENEMY_

#include "Enemy.h"

class SkeletonEnemy : public Enemy
{
public:

	void update(int deltaTime) override;

	void initSprite(ShaderProgram & shaderProgram) override;

	void changeDirection();

};

#endif
