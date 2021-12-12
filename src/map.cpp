#include "map.hpp"

bool* Map::getMap()
{
	return map;
}

int* Map::getMapSize()
{
	return map_size;
}

int Map::getMapLength()
{
	return map_length;
}

void Map::deleteWall(int x, int y)
{
	map[x+y*MAP_SIDE] = 0;
}