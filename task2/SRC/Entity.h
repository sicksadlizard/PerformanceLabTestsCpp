#pragma once

#include <string>
#include "Vector.h"
#include "Sphere.h"
#include <Math.h>
using namespace std;


class Entity
{
private:
	Vector* line;
	Sphere* sphere;

public:
	Entity();
	Entity(Vector* v, Sphere* s);
	void StolenSolve();
	~Entity();
};


