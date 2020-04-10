#include "Entity.h"
#include "Parser.h"
#include <iostream>

Entity::Entity()
{
	this->sphere = NULL;
	this->line = NULL;
};
Entity::Entity(Vector* v, Sphere* s)
{
	this->line = v;
	this->sphere = s;
}
Entity::~Entity()
{
	delete this->sphere;
	delete this->line;
}
void Entity::StolenSolve() //Thank you StackOwerflow
{
	
	/*Delta = b² - 4 * a*c
		with :

	a = (xB - xA)² + (yB - yA)² + (zB - zA)²
		b = 2 * ((xB - xA)(xA - xC) + (yB - yA)(yA - yC) + (zB - zA)(zA - zC))
		c = (xA - xC)² + (yA - yC)² + (zA - zC)² - r²*/
	double a, b, c, xA, xB, xC, yA, yB, yC, zA, zB, zC, r, delta;
	a = b = c = 0;
	xA = line->GetA().GetX();
	xB = line->GetB().GetX();
	xC = sphere->GetCenter().GetX();
	yA = line->GetA().GetY();
	yB = line->GetB().GetY();
	yC = sphere->GetCenter().GetY();
	zA = line->GetA().GetZ();
	zB = line->GetB().GetZ();
	zC = sphere->GetCenter().GetZ();
	r = sphere->GetRadius();
	a = pow(xB - xA, 2) + pow(yB - yA, 2) + pow(zB - zA, 2);
	b = 2 * ((xB - xA) * (xA - xC) + (yB - yA)*(yA - yC) + (zB - zA) * (zA - zC));
	c = pow(xA - xC, 2) + pow(yA - yC, 2) + pow(zA - zC, 2) - pow(r, 2);
	delta = pow(b, 2) - 4 * a * c;

	/*d1=(-b-sqrt(Delta))/(2a) 
	and 
	d2=(-b+sqrt(Delta))/(2a)*/
	if (delta > 0)
	{
		double d1 = (-b - sqrt(delta)) / (2 * a);
		double d2 = (-b + sqrt(delta)) / (2 * a);
		/*x = xA + d*(xB-xA)
		y = yA + d*(yB-yA)
		z = zA + d*(zB-zA)*/
		double x1 = xA + d1 * (xB - xA);
		double y1 = yA + d1 * (yB - yA);
		double z1 = zA + d1 * (zB - zA);
		double x2 = xA + d2 * (xB - xA);
		double y2 = yA + d2 * (yB - yA);
		double z2 = zA + d2 * (zB - zA);
		cout << "[" << x1 << ',' << y1 << ',' << z1 << ']' << endl;
		cout << "[" << x2 << ',' << y2 << ',' << z2 << ']' << endl;
	}
	if (delta == 0)
	{
		//d=-b/2a
		double d = (-b) / (2 * a);
		double x1 = xA + d * (xB - xA);
		double y1 = yA + d * (yB - yA);
		double z1 = zA + d * (zB - zA);
		cout << "[" << x1 << ',' << y1 << ',' << z1 << ']' << endl;
	}
	if (delta < 0)
	{
		setlocale(LC_CTYPE, "rus");
		cout << "Коллизий не найдено" << endl;
	}
}
