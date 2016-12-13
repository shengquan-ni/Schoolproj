#ifndef SQUARE_H
#define SQUARE_H
#include "Shape.h"
class Square:public Shape
{
public:
	Square(double h,string name):Shape(h/2,h/2,name)
	{
		_height=h;
	}
	virtual double area()
	{
		return _height*_height;
	}
	virtual void draw()
	{
		cout<<_name<<endl;
		DrawWithLambda([this](int x,int y){return x==0||y==0||x==_height-1||y==_height-1;},0,0,_height-1,_height-1);
	}
protected:
	double _height;
};
#endif

