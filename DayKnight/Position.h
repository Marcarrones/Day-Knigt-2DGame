#pragma once
class Position
{
public:
	Position(float x, float y);
	Position();

	// Set position
	Position SetPos(float x, float y);
	Position SetX(float x);
	Position SetY(float y);

	// Increments/decrements position
	Position Move(float x, float y);
	Position MoveX(float x);
	Position MoveY(float y);

	float GetX() { return _x;  }
	float GetY() { return _y;  }

private:
	float _x;	
	float _y;
};

