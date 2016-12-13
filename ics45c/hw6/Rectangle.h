#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Square.h"
class Rectangle:public Square
{
public:
	Rectangle(double w,double h,string name):Square(h,name)
	{
		_width=w;
	}
	virtual double area()
	{
		return _width*_height;
	}
	virtual void draw()
	{
		cout<<_name<<endl;
		DrawWithLambda([this](int x,int y){return x==0||y==0||x==_width-1||y==_height-1;},0,0,_height-1,_width-1);
	}
private:
	double _width;
};
#endif

