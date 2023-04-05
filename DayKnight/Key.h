#ifndef _KEY_INCLUDE
#define _KEY_INCLUDE

#include "Entity.h"

class Key: public Entity
{
public:
	Key();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);

	virtual void update(int deltaTime);
	void render();
	void setTileMap(TileMap *tileMap);
	/*
	Para no mostrar la llave deja de hacer render de la llave*/
	void show();
	bool isPicked();

	~Key();
private:
	void initSprite(ShaderProgram &shaderProgram);

	bool showing;
	bool pick;
};

#endif