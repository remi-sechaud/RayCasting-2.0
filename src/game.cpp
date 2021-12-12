#include "game.hpp"

Game::Game()
{
	timer.start();
	player.setMap(map.getMap());
}



void Game::nextFrame()
{		
	refreshRay();
		window.clear();
		window.drawWall(rays,rays_side,player.getAngleY());
		window.drawMap(player.getPos(),map.getMapSize(),map.getMap(),map.getMapLength(),rays,player.getAngle());
		window.drawProj(proj.getPosY(),proj.getRadius());
		window.drawCrossair();
		window.drawGun();

		if(!proj.end())
		{
			proj.move();
		}

		window.displayFlip();

		if(input[0])
		{
			player.goForward();
		}

		if(input[1])
		{
			player.goLeft();
		}

		if(input[2])
		{
			player.goBackward();
		}

		if(input[3])
		{
			player.goRight();
		}

		if(turning_right)
		{
			player.turnRight();
		}
		
		if(turning_left)
		{
			player.turnLeft();
		}

	player.addAngle(mouse_pos[0]-l_mouse_pos[0]);
	player.addAngleY(mouse_pos[1]-l_mouse_pos[1]);
	l_mouse_pos[0] = WIN_X/2;
	l_mouse_pos[1] = WIN_Y/2;
	window.resetMousePos();

	

}

void Game::cleanUp()
{
	window.cleanUp();
}


void Game::refreshRay()
{
	float x = player.getPos()[0];
	float y = player.getPos()[1];

	float temp_x;
	float temp_y;

	float angle = player.getAngle()+(FOV/2);

	float angle_unit = ANGLE_UNIT/(float)ACCURACY;
	for(int i = 0; i < nb_ray;i++)
	{
		temp_x = x;
		temp_y = y;
		angle -= angle_unit;
		while(!isOutside(temp_x,temp_y) && !isTouching(temp_x,temp_y))
		{
			temp_x += cos(angle)*4;
			temp_y += sin(angle)*4;
		}

		rays[i] = sqrt(pow(temp_x-x,2)+pow(temp_y-y,2));

		bool u,d;
		temp_x -= cos(angle)*4;
		temp_y -= sin(angle)*4;

		wherePos(temp_x,temp_y);

		if(pos_x - temp_pos_x > 0)
		{
			u = true;
		}else
		{
			u = false;
		}

		if(pos_y - temp_pos_y > 0)
		{
			d = true;
		}else
		{
			d = false;
		}

		if(d)
		{
			if(u)
			{
				rays_side[i] = 0;
			}else
			{
				rays_side[i] = 1;
			}
		}else
		{
			if(u)
			{
				rays_side[i] = 2;
			}else
			{
				rays_side[i] = 3;
			}
		}

	}
}

bool Game::isOutside(float x, float y)
{
	if(x < 0 || y < 0)
	{
		return true;
	}
	else if(map.getMapSize()[0] < x || map.getMapSize()[1] < y)
	{
		return true;
	}

	return false;
}


bool Game::isTouching(float x, float y)
{
	wherePos(x, y);
	pos_x = temp_pos_x;
	pos_y = temp_pos_y;

	if(map.getMap()[pos_y * (int)MAP_SIDE + pos_x])
	{
		return true;
	}

	return false;
}

void Game::wherePos(float x, float y)
{
	temp_pos_x = (int)x/(int)SQUARE_S;
	temp_pos_y = (int)y/(int)SQUARE_S;
}


void Game::shoot()
{
	proj.init();

	float temp_x;
	float temp_y;

	float angle = player.getAngle();

	temp_x = player.getPos()[0];
	temp_y = player.getPos()[1];

	while(!isOutside(temp_x,temp_y) && !isTouching(temp_x,temp_y))
	{
		temp_x += cos(angle)*8;
		temp_y += sin(angle)*8;
	}

	if(isTouching(temp_x,temp_y))
	{
		map.deleteWall(temp_pos_x,temp_pos_y);
	}
}


