#ifndef _ICOLLIDER
#define _ICOLLIDER


// Forward declarations (evita includes circulares)
class Enemy;
class Key;
class Clock;
class StartEndDoor;
class Gema;
class Health;


class ICollider
{
public:
	// checkCollision(CollisionBox other);
	//virtual bool collideWith(Entity *other) = 0;

	//Enemy1 sera Enemy (clase base enemy)
	virtual bool collideWith(Enemy *other) = 0;

	// Key/Clock podrian tener super clase item con un metodo de pickUp(Player*) o algo pero mucho refator tbh

	virtual bool collideWith(Key *other) = 0;

	virtual bool collideWith(Clock *other) = 0;

	virtual bool collideWith(StartEndDoor *other) = 0;

	virtual bool collideWith(Gema *other) = 0;

	virtual bool collideWith(Health *other) = 0;
};

#endif // !_ICOLLIDER
