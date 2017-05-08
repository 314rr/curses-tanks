//JORDAN'S AND KYLE'S FINAL PROJECT
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>

#if defined(WIN32)
#include <Windows.h>
#include "curses.h"
#else
#include <curses.h>
#include <cstdlib>
#include <unistd.h>
#endif
	
#include "ground.hpp"
#include "player.hpp"

using namespace std;

extern int base_height_divisor;
extern int max_height_divisor;

const double PI = 3.141592653589793238463;

void MySleep(int milliseconds)
{
#if defined(WIN32)
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
}
void DrawScreen(Ground & g, Player * players, int turn)
{
	erase();
	box(stdscr, 0, 0);
	g.Draw();
	players[0].Draw(g);
	players[1].Draw(g);
	players[0].DrawSettings(turn);
	players[1].DrawSettings(turn);
	refresh();
}
//http://www.iforce2d.net/b2dtut/projected-trajectory

void Shoot(Ground & g, Player * players, int turn)
{

	double angle = players[turn].angle / 180.0 * PI;
	double y_component = sin(angle) * players[turn].power * 0.2;
	double x_component = cos(angle) * players[turn].power * 0.2;
	
	double pNx;
	double pNy;
	double time_divisor = 15.0;
	
	if (players[turn].s == RIGHT)
		x_component = -x_component;

	double p0x = players[turn].col;
	double p0y = g.ground.at(players[turn].col);
	int tx = players[turn].col;
	int ty = g.ground.at(players[turn].col);
	
	p0y = LINES - p0y;
	for (int i = 1; i < 5000; i++)
	{
		double di = i / time_divisor;

		pNx = (int)(p0x + di * x_component);
		pNy = p0y + di * y_component + (di * di + di) * -9.8 / time_divisor / 1.5;
		pNy = (int)(LINES - pNy);
		if (pNx < 1 || pNx >= COLS - 2)
			break;
		if (pNy < 1) {
			MySleep(50);
			continue;
		}
		//	if (pNy >= LINES - 2)
		//		break;
		if (pNy > g.ground.at((int)pNx))
		{
			break;
		}
		if (i  > 15)
		{
			if (players[LEFT].Hit((int)pNx, (int)pNy, g))
			{
				players[LEFT].lives--;
				g = Ground(COLS);
				players[0].Initialize(rand() % (COLS / 4), LEFT);
				players[1].Initialize(rand() % (COLS / 4) + 3 * COLS / 4 - 2, RIGHT);
				break;
			}
			if (players[RIGHT].Hit((int)pNx, (int)pNy, g))
			{
				players[RIGHT].lives--;
				g = Ground(COLS);
				players[0].Initialize(rand() % (COLS / 4), LEFT);
				players[1].Initialize(rand() % (COLS / 4) + 3 * COLS / 4 - 2, RIGHT);
				break;
			}
		}

		move((int)pNy - 1, (int)pNx + 1);
		addch('*');
		refresh();
		MySleep(25);
	}

}

int main(int argc, char * argv[])
{
	srand((unsigned int)time(nullptr));

	int turn = 0;
	bool keep_going = true;
	Ground g = Ground(COLS);
	Player players[2];

	initscr();
	noecho();
	keypad(stdscr, 1);
	while (true)
	{
		string s = "Welcome to the Tank Game! Press I for information on how to play the game or press any key to continue!";
		move(0,0);
		addstr(s.c_str());
		refresh();
		char a = getch();
		if (a == 'i' || a == 'I')
		{
			erase();
			string s = "The up and down keys control the power, The left and right keys control the angle. The spacebar is to shoot your bullet! Press any key to continue to the game!";
			move(0,0);
			addstr(s.c_str());
			refresh();
			getch();
			break;
		}
		else if( a != 'i' || a != 'I')
			break;
	
	}
	g.InitializeGround();
	players[0].Initialize(rand() % (COLS / 4), LEFT);
	players[1].Initialize(rand() % (COLS / 4) + 3 * COLS / 4 - 2, RIGHT);
	players[0].lives = 3;
	players[1].lives = 3;

	DrawScreen(g, players,turn);
	while (keep_going)
	{
		if (players[LEFT].lives == 0 || players[RIGHT].lives == 0)
		{
			erase();
			string s = "WOULD YOU LIKE TO PLAY AGAIN (y/n)?";
			move(0,0);
			addstr(s.c_str());
			refresh();
			char a = getch();
			if (a == 'y' || a == 'Y')
			{
				refresh();
				players[LEFT].lives = 3;
				players[RIGHT].lives = 3;
				turn = 0;
				DrawScreen(g, players, turn);
			}
			else if (a != 'y' || a != 'Y')
			{
				erase();
				string s = "Thanks for playing! Press any key to exit!";
				move(0,0);
				addstr(s.c_str());
				refresh();
				getch();
				exit(0); 
			}
			else
				break; 
		} 
		bool show_char = false;
		int c = getch();
		switch (c)
		{
		case 27:
			keep_going = false;
			break;

		case KEY_DOWN:
			players[turn].PowerDown();
			break;

		case KEY_UP:
			players[turn].PowerUp();
			break;

		case KEY_RIGHT:
			players[turn].AngleUp();
			break;

		case KEY_LEFT:
			players[turn].AngleDown();
			break;

		case 10:
		case ' ':
			Shoot(g, players, turn);
			turn = 1 - turn;
			break;

		default:
			show_char = true;
			break;
		}
		DrawScreen(g, players, turn);
		if (show_char) 
		{
			move(0, 1);
			stringstream ss;
			ss << setw(4) << c << " ";
			addstr(ss.str().c_str());
			refresh();
		}
	}
	erase();
	addstr("Hit any key to exit");
	refresh();
	getch();
	echo();
	endwin();
	return 0;
}
