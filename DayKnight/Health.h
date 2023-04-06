#ifndef _HEALTH_INCLUDE
#define _HEALTH_INCLUDE

#include "Entity.h"
class Health : public Entity
{
public:
	Health();
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
	~Health();

private:
	bool picked;
	float timeToStop;
	void initSprite(ShaderProgram &shaderProgram);
};

#endif