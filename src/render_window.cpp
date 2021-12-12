#include <SDL.h>
#include "render_window.hpp"

RenderWindow::RenderWindow()
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,WIN_X, WIN_Y,SDL_WINDOW_ALLOW_HIGHDPI);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
}

void RenderWindow::displayFlip()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::drawMap(float* pos,int* win_size,bool* grid,int map_length,float* rays,float p_angle)
{

	int side = sqrt(map_length);
	int square_size = win_size[0]/5/side;

	for(int i = 0; i < side; i++)
	{
		for(int j = 0; j < side; j++)
		{
			if(grid[i*side+j])
			{
				SDL_SetRenderDrawColor(renderer,50,180,120,255);
			}	
			else
				SDL_SetRenderDrawColor(renderer,120,120,220,255);

			drawRect(j*square_size,i*square_size,square_size,square_size);
		}
	}

	SDL_SetRenderDrawColor(renderer,200,200,20,255);
	float angle = p_angle+FOV/2;
	float unit_angle = ANGLE_UNIT/ACCURACY;
	for(int i = 0; i < DEGREE_FOV*ACCURACY; i++)
	{
		angle -= unit_angle;
		SDL_RenderDrawLine(renderer,pos[0]/5,pos[1]/5,(pos[0]+(rays[i]*cos(angle)))/5,(pos[1]+rays[i]*sin(angle))/5);
	}

	drawCircle(5,pos[0]/5,pos[1]/5);


}

void RenderWindow::drawCircle(int radius,int pos_x,int pos_y)
{

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	int x_min = -radius;
	int x_max = radius;
	for(int x = x_min ; x < x_max ; x++)
	{
		int y = sqrt((radius*radius)-(x*x));
		SDL_RenderDrawLine(renderer,pos_x-x,pos_y+y,pos_x-x,pos_y-y);
	}

}


void RenderWindow::drawRect(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_RenderFillRect(renderer,&rect);
}


void RenderWindow::drawWall(float* rays,short* rays_side,float angle_y)
{

	float gap = WIN_X/(DEGREE_FOV*ACCURACY);

	angle_y *= 400;

	for(int i = 1; i < DEGREE_FOV*ACCURACY+1; i++)
	{

 		
		/*SDL_SetRenderDrawColor(renderer,255,255,255,255);

 		SDL_RenderDrawLine(renderer,gap*i,WIN_Y/2, gap*(i), WIN_Y);*/

		if(rays_side[DEGREE_FOV*ACCURACY-i] == 0)
		{
			SDL_SetRenderDrawColor(renderer,255,255,(int)rays[DEGREE_FOV*ACCURACY-i]/10,255);
		}
		else if(rays_side[DEGREE_FOV*ACCURACY-i] == 1)
		{
			SDL_SetRenderDrawColor(renderer,(int)rays[DEGREE_FOV*ACCURACY-i]/10,255,255,255);
		}
		else if(rays_side[DEGREE_FOV*ACCURACY-i] == 2)
		{
			SDL_SetRenderDrawColor(renderer,(int)rays[DEGREE_FOV*ACCURACY-i]/10,(int)rays[DEGREE_FOV*ACCURACY-i]/10,255,255);
		}else if(rays_side[DEGREE_FOV*ACCURACY-i] == 3)
		{
			SDL_SetRenderDrawColor(renderer,255,(int)rays[DEGREE_FOV*ACCURACY-i]/10,255,255);
		}



		/*SDL_RenderDrawLine(renderer,gap*i,WIN_Y/2 - pow(WIN_Y-rays[DEGREE_FOV-i],1.60)/100, gap*(i), WIN_Y/2 + pow(WIN_Y-rays[DEGREE_FOV-i],1.60)/100);*/

		if(WIN_Y - rays[DEGREE_FOV*ACCURACY-i]/2 > WIN_Y/2 && rays[DEGREE_FOV*ACCURACY-i]/2 < WIN_Y/2)
		{
			SDL_RenderDrawLine(renderer,gap*i,WIN_Y - rays[DEGREE_FOV*ACCURACY-i]/2-angle_y, gap*(i), rays[DEGREE_FOV*ACCURACY-i]/2-angle_y);
		}		

		SDL_SetRenderDrawColor(renderer,255,255,255,255);

		if(WIN_Y/2-rays[DEGREE_FOV*ACCURACY-i]/2 > 0)
		{
			SDL_RenderDrawLine(renderer,gap*i+1,WIN_Y -rays[DEGREE_FOV*ACCURACY-i]/2-angle_y, gap*(i)+1, WIN_Y);
		}	
		else
		{
			SDL_RenderDrawLine(renderer,gap*i+1,WIN_Y/2-angle_y, gap*(i)+1, WIN_Y);
		}
	}	
}

void RenderWindow::resetMousePos()
{
	SDL_WarpMouseInWindow(window, WIN_X/2, WIN_Y/2);
}


void RenderWindow::drawCrossair()
{
	drawRect(WIN_X/2-20,WIN_Y/2-3,13,6);
	drawRect(WIN_X/2+7,WIN_Y/2-3,13,6);

	drawRect(WIN_X/2-3,WIN_Y/2-20,6,13);
	drawRect(WIN_X/2-3,WIN_Y/2+7,6,13);
}

void RenderWindow::drawGun()
{
	SDL_SetRenderDrawColor(renderer,25, 111, 61,255);

	for(int i; i < 200; i++)
	{
		SDL_RenderDrawLine(renderer,WIN_X/2-250+i,WIN_Y-i,WIN_X/2+250-i,WIN_Y-i);
	}

	SDL_SetRenderDrawColor(renderer,255, 255, 255,255);

	SDL_RenderDrawLine(renderer,WIN_X/2-50,WIN_Y-200,WIN_X/2+50,WIN_Y-200);

	SDL_RenderDrawLine(renderer,WIN_X/2-250,WIN_Y,WIN_X/2-50,WIN_Y-200);

	SDL_RenderDrawLine(renderer,WIN_X/2+250,WIN_Y,WIN_X/2+50,WIN_Y-200);
}

void RenderWindow::drawProj(float y, float r)
{
	drawCircle(r,WIN_X/2,y);
}
