#pragma once

class Vec2d
{
public:
	double x, y;

	Vec2d();
	Vec2d(double l, double c);
	
	Vec2d operator+(const double&);
	Vec2d operator+(const Vec2d&);
	Vec2d operator*(const double&);
	Vec2d operator*(const int&);
	/*void operator+(const double&);
	void operator*(const double&);
	void operator*(const int&);*/
};
