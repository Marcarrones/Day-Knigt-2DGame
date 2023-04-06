#ifndef _SKULLENEMY_
#define _SKULLENEMY_

#include "Enemy.h"

class SkullEnemy : public Enemy
{
public:

	void init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram) override;

	void update(int deltaTime) override;

	void initSprite(ShaderProgram & shaderProgram) override;

	void changeDirection();

};

#endif // !_SKULLENEMY_
