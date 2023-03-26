#include "Position.h"



Position::Position(float x, float y)
{
	_x = x;
	_y = y;
}

Position::Position()
{
	this->Position::Position(0, 0);
}

Position Position::SetPos(float x, float y)
{
	_x = x;
	_y = y;
	return *this;
}

Position Position::SetX(float x)
{
	_x = x;
	return *this;
}

Position Position::SetY(float y)
{
	_y = y;
	return *this;
}

Position Position::Move(float x, float y)
{
	_x += x;
	_y += y;
	return *this;
}

Position Position::MoveX(float x)
{
	_x += x;
	return *this;
}

Position Position::MoveY(float y)
{
	_y += y;
	return *this;
}


