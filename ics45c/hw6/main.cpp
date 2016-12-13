#include "Circle.h"
#include "Triangle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Picture.h"
int main()
{
	Picture p;
	p.Add(new Triangle(5,5,"FirstTriangle"));
	p.Add(new Triangle(4,3,"SecondTriangle"));
	p.Add(new Circle(5,"FirstCircle"));
	p.Add(new Circle(10,"SecondCircle"));
	p.Add(new Square(5,"FristSquare"));
	p.Add(new Square(10,"SecondSquare"));
	p.Add(new Rectangle(8,4,"FirstRectangle"));
	p.Add(new Rectangle(4,8,"SecondRectangle"));
	p.drawAll();
	cout<<"The total area of the shapes on this picture is "<<p.totalArea()<<" square units"<<endl;
	return 0;
}
