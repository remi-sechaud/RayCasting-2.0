#include "player.hpp"

float Player::getAngle()
{
	return angle;
} 

float Player::getAngleY()
{
	return angle_y;
} 

float* Player::getPos()
{
	return pos;
}

void Player::goForward()
{
	pos[0] += cos(angle);
	pos[1] += sin(angle);

	if(isIn())
	{
		pos[0] -= cos(angle);
		pos[1] -= sin(angle);
	}
}

void Player::goBackward()
{
	pos[0] -= cos(angle);
	pos[1] -= sin(angle);

	if(isIn())
	{
		pos[0] += cos(angle);
		pos[1] += sin(angle);
	}
}

void Player::goRight()
{
	pos[0] += cos(angle+s_PI);
	pos[1] += sin(angle+s_PI);

	if(isIn())
	{
		pos[0] -= cos(angle+s_PI);
		pos[1] -= sin(angle+s_PI);
	}
}

void Player::goLeft()
{
	pos[0] -= cos(angle+s_PI);
	pos[1] -= sin(angle+s_PI);

	if(isIn())
	{
		pos[0] += cos(angle+s_PI);
		pos[1] += sin(angle+s_PI);
	}
}

void Player::turnRight()
{
	angle += 0.05;
}

void Player::turnLeft()
{
	angle -= 0.05;
}

void Player::addAngle(int difference)
{
	angle += (float)difference/(float)1000;
}

void Player::addAngleY(int difference)
{
	angle_y += (float)difference/(float)1000;
}

void Player::setMap(bool* map)
{
	map_p = map;
}

bool Player::isIn()
{
	if(map_p[(int)pos[1]/(int)SQUARE_S*MAP_SIDE + (int)pos[0]/(int)SQUARE_S])
	{
		return true;
	}
	else if((pos[0] < 0 || pos[1] < 0))
	{
		return true;
	}

	return false;
}