#pragma once
#include <cmath>
#include <iostream>
#include "const.hpp"

class Projectile
{
	public:
		float getPosY();
		float getRadius();
		void move();
		bool end();
		void init();

	private:
		float pos_y = WIN_Y - 200;
		float radius = 30;

};