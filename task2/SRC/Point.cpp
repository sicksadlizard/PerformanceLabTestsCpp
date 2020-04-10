#include "Point.h"

Point::Point(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
double Point::GetX()
{
	return this->x;
}
double Point::GetY()
{
	return this->y;
}
double Point::GetZ()
{
	return this->z;
}