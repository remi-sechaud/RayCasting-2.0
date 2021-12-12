#pragma once
#include <SDL.h>
#include <cmath>
#include "const.hpp"
#include <iostream>

using namespace std;

class RenderWindow
{
	public:
		RenderWindow();
		void cleanUp();
		void clear();
		void displayFlip();
		void drawMap(float* pos,int* win_size,bool* grid,int map_length,float* rays, float p_angle);
		void drawCircle(int radius,int pos_x,int pos_y);
		void drawRect(int x, int y, int w, int h);
		void drawCrossair();
		void drawWall(float* rays,short* rays_side,float angle_y);
		void resetMousePos();
		void drawGun();
		void drawProj(float y, float r);
		
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

};