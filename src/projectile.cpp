#include "projectile.hpp"

float Projectile::getPosY()
{
	return pos_y;
}

float Projectile::getRadius()
{
	return radius;
}

void Projectile::move()
{
	pos_y -= 20;
	radius -= 2;
}

bool Projectile::end()
{
	if(pos_y < WIN_Y/2)
	{
		return true;
	}

	return false;
}

void Projectile::init()
{
	pos_y = WIN_Y - 200;
	radius = 30;
}


