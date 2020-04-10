#pragma once
#include "Point.h"
class Vector
{
private:
	Point* a;
	Point* b;
public:
	Vector(Point, Point);
	Point GetA();
	Point GetB();
	~Vector();
};

