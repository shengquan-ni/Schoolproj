#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"
class Triangle: public Shape
{
public:
	Triangle(double h,double b,string name):Shape(b/2,h/2,name)
	{
		_height=h;
		_base=b;
	}

	virtual double area()
	{
		return _height*_base/2;
	}

	virtual void draw()
	{
		cout<<_name<<endl;
		DrawWithLambda([this](int x,int y){return x==0||y==0||(x<0 && y<=x*_height/(_base/2)+_height)||(x>0&& y<=-x*_height/(_base/2)+_height);},_centerX,0,_height-1,_base-1);
	}
private:
	double _height;
	double _base;
};
#endif
