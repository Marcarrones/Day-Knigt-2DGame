#ifndef _COLLISION_BOX
#define _COLLISION_BOX

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"

class CollisionBox
{
	struct Point {
		int x = 0;
		int y = 0;

		Point(int X, int Y) {
			x = X;
			y = Y;
		}
	};

	struct Rectangle
	{
		Point upperLeft = Point(0, 0);
		Point lowerRight = Point(0, 0);

		Rectangle(Point ul, Point lr) {
			upperLeft = ul;
			lowerRight = lr;
		}
	};
public:
	CollisionBox();

	~CollisionBox();
	
	void init(glm::ivec2 *position, int height, int width, bool isStatic, ShaderProgram *shaderProgram);

	void render();

	int getHeight() { return _height; }
	int getWidth() { return _height; }

	bool CheckColission(CollisionBox other);
	Rectangle getRectangle();

private:
	int _height;
	int _width;
	bool _isStatic;
	glm::ivec2 *_position;
	Sprite  *_debugBox;
};

#endif // _COLLISION_BOX