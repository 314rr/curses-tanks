#include "Vec2d.hpp"

Vec2d::Vec2d()
{
	y = 0;
	x = 0;
}

Vec2d::Vec2d(double l, double c)
{
	y = l;
	x = c;
}

Vec2d Vec2d::operator+(const double & a)
{
	Vec2d retval = Vec2d();
	retval.y += a;
	retval.x += a;
	return retval;
}

Vec2d Vec2d::operator+(const Vec2d & other)
{
	Vec2d retval = Vec2d();
	retval.y += other.y;
	retval.x += other.x;
	return retval;
}

Vec2d Vec2d::operator*(const double & m)
{
	Vec2d retval = Vec2d();
	retval.y *= m;
	retval.x *= m;
	return retval;
	
}

Vec2d Vec2d::operator*(const int & m)
{
	double m2 = double(m);
	Vec2d retval = Vec2d();
	retval.y *= m2;
	retval.x *= m2;
	return retval;

}

//Vec2d::Vec2d()
//{
//	y = 0;
//	x = 0;
//}
//
//Vec2d::Vec2d(double l, double c)
//{
//	y = l;
//	x = c;
//}
//
//void Vec2d::operator+(const double & a)
//{
//	y += a;
//	x += a;
//}
//void Vec2d::operator*(const double & m)
//{
//	y *= m;
//	x *= m;
//}
//
//void Vec2d::operator*(const int & m)
//{
//	double m2 = double(m);
//	y *= m2;
//	x *= m2;
//}