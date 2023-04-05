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

	void setTileMap(TileMap *tileMap);
	/* Para no mostrar la llave deja de hacer render de la llave*/
	void show();
	bool isPicked();

	~Key();
private:
	void initSprite(ShaderProgram &shaderProgram);

	bool showing;
	bool pick;
};

#endif