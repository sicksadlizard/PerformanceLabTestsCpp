#include "Vector.h"

Vector::Vector(Point a, Point b)
{
	this->a = new Point(a.GetX(), a.GetY(), a.GetZ());
	this->b = new Point(b.GetX(), b.GetY(), b.GetZ());
}
Vector::~Vector()
{
	delete this->a;
	delete this->b;
}
Point Vector::GetA()
{
	return *this->a;
}
Point Vector::GetB()
{
	return *this->b;
}