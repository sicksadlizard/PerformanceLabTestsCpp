#include "Radius.h"

Radius::Radius()
{
	this->r = 0;
}
Radius::Radius(double r)
{
	this->r = r;
}
const double Radius::GetRadius()
{
	return this->r;
}