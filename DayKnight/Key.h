#ifndef _KEY_INCLUDE
#define _KEY_INCLUDE

#include "Entity.h"

class Key: public Entity
{
public:

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);

	void update(int deltaTime) override;
	
	void render();

	virtual bool collidedBy(ICollider *collider) override
		{ return collider->collideWith(this); }

	/* Para no mostrar la llave deja de hacer render de la llave*/
	void show();
	void pickUp();

	bool isPicked();
	bool canBePicked() { return (showing && !pick); }

private:
	void initSprite(ShaderProgram &shaderProgram);

	bool showing = false;
	bool pick = false;
};

#endif