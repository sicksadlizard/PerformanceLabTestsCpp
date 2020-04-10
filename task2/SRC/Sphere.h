#pragma once
#include "Point.h"
#include "Radius.h"
class Sphere
{
private:
	Point* center;
	Radius* r;
public:
	Sphere();
	Sphere(Point, Radius);
	Point GetCenter();
	double GetRadius();
	~Sphere();
};

