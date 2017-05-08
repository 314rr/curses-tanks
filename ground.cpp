#if defined(WIN32)
#include "curses.h"
#else
#include <curses.h>
#include <cstdlib>
#endif

#include "ground.hpp"

int base_height_divisor = 8;
int max_height_divisor = 2;

Ground::Ground(size_t s)
{
	ground.resize(s);
	int h = rand() % 5 + (LINES - 10);
	int variation;
	for (size_t i = 0; i < s; i++)
	{
		if (h < (0 + 2))
			h = 3;
		else if (h >= LINES - 2)
			h = ground.at(i - 1);// -3;
		else if (i % 3 == 0)
		{
			variation = rand() % 3 - 1;
			h = h - variation;
		}
		ground[i] = h;
	}
}


void Ground::InitializeGround()
{
	int current_height = LINES - LINES / base_height_divisor;
	//int maximum_height = lines / max_height_divisor;

	for (int i = 1; i < COLS - 1; i++) {
		int h = current_height;
		int r = rand() % 10000;
		if (r < 800) {
			current_height++;
			if (current_height >= LINES - 2)
				current_height = LINES - 2;
		}
		else if (r < 1600) {
			current_height--;
			if (current_height < 1)
				current_height = 1;
		}
		ground.push_back(h);
	}
}

void Ground::Draw()
{
	for (size_t i = 0; i < ground.size(); i++) {
		mvaddch(ground.at(i), i + 1, '-');
	}
}
void Ground::Explode(int position)
{
	if(ground.at(position) < LINES - 2)
		ground.at(position)++;
	
	/*for (int i = -1; i < 2; i++)
	{
		if((ground.at(position + i - 1) - ground.at( position + i) <= 2) && ground.at(position + i) < LINES - 2)
			ground.at(position + i)++;
	}*/
}
