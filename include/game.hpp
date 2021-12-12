#pragma once
#include <SDL.h>
#include <cmath>
#include "render_window.hpp"
#include "map.hpp"
#include "player.hpp"
#include "timer.hpp"
#include "const.hpp"
#include "projectile.hpp"

using namespace std;

class Game
{
	public:
		Game();
		void nextFrame();
		void cleanUp();
		void refreshRay();
		bool isOutside(float x,float y);
		bool isTouching(float x,float y);
		void wherePos(float x, float y);
		void shoot();
		bool input[4] = {false,false,false,false};
		bool turning_right = false;
		bool turning_left = false;

		int mouse_pos[2];
		int l_mouse_pos[2] = {WIN_X/2,WIN_Y/2};

		int pos_x;
		int pos_y;

		int temp_pos_x;
		int temp_pos_y;
		
	private:
		Projectile proj;
		RenderWindow window;
		Map map;
		Player player;
		Timer timer;

		float rays[DEGREE_FOV*ACCURACY];
		short rays_side[DEGREE_FOV*ACCURACY];

		int nb_ray = DEGREE_FOV*ACCURACY;

		int x,y;





		


};