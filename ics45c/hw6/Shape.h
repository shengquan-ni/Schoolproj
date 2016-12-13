#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <string>
#include <functional>
#include <math.h>
using namespace std;
class Shape
{
public:
	Shape(int centerX,int centerY,string name)
	{
		_centerX=centerX;
		_centerY=centerY;
		_name=name;
	};
	virtual double area()=0;
	virtual void draw()=0;
protected:
	int _centerX;
	int _centerY;
	string _name;
};

static void DrawWithLambda(function<bool(int,int)> f,int centerx,int centery,int height,int width)
{
	for(int i=height;i>=0;i--)
	{
		for(int j=0;j<=width;j++)
		{
			if(f(j-centerx,i-centery))
				cout<<'*';
			else
				cout<<' ';
		}
		cout<<endl;
	}
}



#endif
