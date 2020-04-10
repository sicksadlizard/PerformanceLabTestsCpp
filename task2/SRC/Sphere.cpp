#include "Sphere.h"

Sphere::Sphere()
{
	this->center = nullptr;
	this->r = nullptr;
}
Sphere::Sphere(Point p, Radius r)
{
	this->center = new Point(p);
	this->r = new Radius(r);
}
Sphere::~Sphere()
{
	delete center;
	delete r;
}
Point Sphere::GetCenter()
{
	return *this->center;
}

double Sphere::GetRadius()
{
	return this->r->GetRadius();
}