#ifndef _GEMA_INCLUDE
#define _GEMA_INCLUDE

#include "Entity.h"
class Gema: public Entity
{
public:
	Gema();
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime) override;
	void render();
	virtual bool collidedBy(ICollider *collider) override
	{
		return collider->collideWith(this);
	}

	void setTileMap(TileMap *tileMap);
	void pick();
	bool ispicked();
	~Gema();
private:
	bool picked;
	void initSprite(ShaderProgram &shaderProgram);
};

#endif