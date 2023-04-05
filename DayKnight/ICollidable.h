#ifndef _ICOLLIDABLE
#define _ICOLLIDABLE

//#include "ICollider.h"
//Foward declaration
class ICollider;

class ICollidable
{
public:
	virtual bool collidedBy(ICollider *collider) = 0 ;
};
#endif // !_ICOLIDABLE

