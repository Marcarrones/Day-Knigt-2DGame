#include "CollisionBox.h"
#include <math.h>

#include "Scene.h"




CollisionBox::CollisionBox()	{ }

CollisionBox::~CollisionBox()	{	}

void CollisionBox::init(glm::ivec2 *position, int height, int width, ShaderProgram *shaderProgram)
{
	_position = position;
	_height = height;
	_width = width;
	t.createEmptyTexture(width, height);
	_debugBox = Sprite::createSprite(glm::vec2(height, width),glm::vec2(0,0), &t, shaderProgram);
}

void CollisionBox::render() {

	_debugBox->setPosition((*_position)+glm::ivec2(SCREEN_X,SCREEN_Y));
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	_debugBox->render();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool CollisionBox::CheckColission(CollisionBox other)
{
	Rectangle thisRect = getRectangle();
	Rectangle otherRect = other.getRectangle();

	// x axis
	if (thisRect.lowerRight.x < otherRect.upperLeft.x || 
		thisRect.upperLeft.x > otherRect.lowerRight.x) 
		return false;
	
	// y axis
	if (thisRect.lowerRight.y < otherRect.upperLeft.y ||
		thisRect.upperLeft.y > otherRect.lowerRight.y)
		return false;

	return true;
}

CollisionBox::Rectangle CollisionBox::getRectangle (){
	return Rectangle(
		Point(_position->x			,_position->y), 
		Point(_position->x + _width	, _position->y + _height) 
	);
}

