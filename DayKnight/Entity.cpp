#include "Entity.h"

//Entity::Entity() {	}

void Entity::init(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram)
{
	if (sprite == NULL) {
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	}

	tileMapDispl = tileMapPos;
	collider.init(&posEntity, 32, 32, &shaderProgram);
	
	initSprite(shaderProgram);
}

void Entity::update(int deltaTime)
{

}

void Entity::render()
{
	sprite->render();
	if (showCollision) collider.render();
}


void Entity::setTileMap(TileMap * tileMap)
{
	map = tileMap;
}

void Entity::setPosition(const glm::vec2 & pos)
{
	posEntity = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEntity.x), float(tileMapDispl.y + posEntity.y)));
}
