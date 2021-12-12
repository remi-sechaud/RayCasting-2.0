#pragma once
#include <cmath>
#include <iostream>
#include "const.hpp"

class Player
{
	public:
		float getAngle();
		float getAngleY();
		float* getPos();
		void goForward();
		void goBackward();
		void goLeft();
		void goRight();
		void turnLeft();
		void turnRight();
		void setMap(bool* map);
		bool isIn();

		void addAngle(int difference);
		void addAngleY(int difference);

		
	private:
		float pos[2] = {250,300};
		float angle = 0;
		float angle_y = 0;
		bool* map_p;
		int l = MAP_L;
		int s = MAP_S;

};