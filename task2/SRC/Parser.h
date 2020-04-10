#pragma once
#include <string>
#include "Point.h"
#include "Vector.h"
#include "Entity.h"
#include <stdexcept>
//DEFINE TAGS
#define PARENT	"parent"
#define SPHERE	"sphere"
#define CENTER	"center"
#define RADIUS	"radius"
#define LINE	"line"
//-----------

using namespace std;

class Parser
{
public:
	static string GetInbraceString(string raw, char openingBrace, char clothingBrace);
	static string GetTag(string);
	static Vector* ParseVector(string);
	static Point ParsePoint(string);
	static double ParseDouble(string);
	static string ignoreBaseBraces(string);
	static Entity* ParseInputString(string);
	static Sphere* ParseSphere(string);
};

