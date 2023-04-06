#ifndef _VAMPIRE_
#define _VAMPIRE_

#include "Enemy.h"

class VampireEnemy : public Enemy
{
public:
	void update(int deltatime) override;

	void initSprite(ShaderProgram & shaderProgram) override;

	void changeDirection();

	enum VAMP_STATE {
		VAMPIRE, BAT
	};

private:
	void transform();

	void vampireUpdate(int deltaTime);
	void batUpdate(int deltaTime);

	int transformCD = 3000;
	int currentCD = 3000;
	bool transforming = false;
	int transformDur = 0;

	int vertDirection = -1; // -1 UP // 1 DOWN
	
	int vertSpeed = 1;
	int horSpeed = 2;

	VAMP_STATE currentState = VAMPIRE;
};

#endif // !_VAMPIRE_
