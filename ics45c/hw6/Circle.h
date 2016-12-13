#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
#define PI 3.1415926535
class Circle:public Shape
{
public:
	Circle(double radius,string name):Shape(radius,radius,name)
	{
		_radius=radius;
	}
	virtual double area()
	{
		return _radius*_radius*PI;
	}

	virtual void draw()
	{
		cout<<_name<<endl;
		DrawWithLambda([this](int x,int y){return sqrt(x*x+y*y)==_radius;},_centerX,_centerY,_radius*2,_radius*2);
	}

private:
	double _radius;
};
#endif 
